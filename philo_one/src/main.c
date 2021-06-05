/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:49:22 by aashara-          #+#    #+#             */
/*   Updated: 2021/06/05 23:31:12 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo.h"

# define PHILO_ARGS "number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"

static void	philo_free_data(t_philo_data *data)
{
	int	i;

	free(data->philozophers);
	data->philozophers = NULL;
	i = -1;
	while (++i < data->params[0])
		pthread_mutex_destroy(data->forks + i);
	data->forks = NULL;
}

static int	philo_init_data(t_philo_data *data)
{
	int	i;

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
	memset((void*)data, 0, sizeof(t_philo_data));
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
	int			i;
	pthread_t	thread;

	i = -1;
	data->start_time = philo_get_current_time();
	while (++i < data->params[0])
	{
		if (pthread_create(&thread, NULL, philo_run,(void*)data->philozophers + i))
		{
			dprintf(2, "Cannot create thread\n");
			return (PHILO_FAILURE);
		}
		if (pthread_detach(thread) != 0)
		{
			dprintf(2, "Cannot detach thread\n");
			return (PHILO_FAILURE);
		}
	}
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
