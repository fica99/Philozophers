/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:49:22 by aashara-          #+#    #+#             */
/*   Updated: 2021/06/06 21:38:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo.h"

# define PHILO_ARGS "number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"

static void	philo_free_data(t_philo_data *data)
{
	int	i;
	int	res;

	if (data == NULL)
		return;
	if (data->philozophers != NULL)
	{
		free(data->philozophers);
		data->philozophers = NULL;
	}
	i = -1;
	while (++i < data->params[0])
	{
		ASSERT(data->forks + i != NULL);
		res = pthread_mutex_destroy(data->forks + i);//maybe add protection
		ASSERT(res == 0);
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
}

static int	philo_init_data(t_philo_data *data)
{
	int	i;

	ASSERT(data != NULL);
	ASSERT(data->params[0] > 0);
	if (!(data->philozophers = (t_philo*)malloc(sizeof(t_philo) *
				data->params[0])) ||
		!(data->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) *
				data->params[0])))
	{
		dprintf(2, "Cannot allocate memory\n");
		return (PHILO_FAILURE);
	}
	i = -1;
	while (++i < data->params[0])
	{
		data->philozophers[i].number = i + 1;
		data->philozophers[i].data = data;
		data->philozophers[i].left_fork = i;
		data->philozophers[i].right_fork = (i + 1) % data->params[0];
		if (pthread_mutex_init(data->forks + i, NULL))
		{
			dprintf(2, "Cannot init mutexes for forks\n");
			return (PHILO_FAILURE);
		}
	}
	return (PHILO_SUCCESS);
}

static int	philo_init(int argc, char **argv, t_philo_data *data)
{
	ASSERT(data != NULL);
	memset((void*)data, 0, sizeof(t_philo_data));//add protect
	if (philo_init_params(argc, argv, data->params) == PHILO_FAILURE)
	{
		dprintf(2, "\nUsage\n  %s %s\n", argv[0], PHILO_ARGS);
		return (PHILO_FAILURE);
	}
	if (philo_validate_params(data->params) == PHILO_FAILURE)
		return (PHILO_FAILURE);
	if (philo_init_data(data) == PHILO_FAILURE)
	{
		dprintf(2, "Error in data initialization\n");
		philo_free_data(data);
		return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}

static int	philo_run_threads(t_philo_data *data)
{
	ASSERT(data != NULL);
	ASSERT(data->params != NULL);
	ASSERT(data->params[0] > 0);
	int			i;
	pthread_t	threads[data->params[0]];

	i = -1;
	data->start_time = philo_get_current_time();
	while (++i < data->params[0])
	{
		data->philozophers[i].last_eat_time = data->start_time;
		if (pthread_create(threads + i, NULL, philo_run, (void*)(data->philozophers + i)) != 0)
		{
			dprintf(2, "Cannot create thread\n");
			return (PHILO_FAILURE);
		}
		if (pthread_detach(threads[i]) != 0)
		{
			dprintf(2, "Cannot detach thread\n");
			return (PHILO_FAILURE);
		}
	}
	philo_main_thread(data);
	return (PHILO_SUCCESS);
}

int			main(int argc, char **argv)
{
	t_philo_data	data;

	if (philo_init(argc, argv, &data) == PHILO_FAILURE)
		return (EXIT_FAILURE);
	if (philo_run_threads(&data) == PHILO_FAILURE)
	{
		philo_free_data(&data);
		return (EXIT_FAILURE);
	}
	philo_free_data(&data);
	return (EXIT_SUCCESS);
}
