/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:49:22 by aashara-          #+#    #+#             */
/*   Updated: 2021/07/18 23:48:39 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo_error.h"
#include "philo.h"

static void	philo_free_data(t_philo_data *data)
{
	int	i;

	PHILO_ASSERT(data != NULL);
	PHILO_ASSERT(data->philozophers != NULL);
	PHILO_ASSERT(data->params != NULL);
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
		PHILO_ASSERT(data->forks + i != NULL);
		if (pthread_mutex_destroy(data->forks + i) != 0)
			PHILO_ERROR_RETURN(, "Cannot destroy mutex\n");
	}
	if (data->forks != NULL)
	{
		free(data->forks);
		data->forks = NULL;
	}
}

static int	philo_init_data(t_philo_data *data)
{
	int	i;

	PHILO_ASSERT(data != NULL);
	PHILO_ASSERT(data->params != NULL);
	PHILO_ASSERT(data->params[0] > 0);
	if (!(data->philozophers = (t_philo*)malloc(sizeof(t_philo) *
				data->params[0])) ||
		!(data->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) *
				data->params[0])))
		PHILO_ERROR_RETURN(PHILO_FAILURE, "Cannot allocate memory\n");
	i = -1;
	while (++i < data->params[0])
	{
		data->philozophers[i].number = i + 1;
		data->philozophers[i].data = data;
		data->philozophers[i].left_fork = i;
		data->philozophers[i].right_fork = (i + 1) % data->params[0];
		if (pthread_mutex_init(data->forks + i, NULL))
			PHILO_ERROR_RETURN(PHILO_FAILURE, "Cannot init mutexes for forks\n");
	}
	return (PHILO_SUCCESS);
}

static int	philo_init(int argc, char **argv, t_philo_data *data)
{
	PHILO_ASSERT(data != NULL);
	memset((void*)data, 0, sizeof(t_philo_data));
	if (philo_init_params(argc, argv, data->params) == PHILO_FAILURE)
		PHILO_ERROR_RETURN(PHILO_FAILURE, "\nUsage\n  %s %s %s %s %s [%s]\n", argv[0], PHILO_NB_PHILO,
		PHILO_TIME_TO_DIE, PHILO_TIME_TO_EAT, PHILO_TIME_TO_SLEEP, PHILO_NB_EATINGS);
	if (philo_validate_params(data->params) == PHILO_FAILURE)
		return (PHILO_FAILURE);
	if (philo_init_data(data) == PHILO_FAILURE)
	{
		PHILO_ERROR("Error in data initialization\n");
		philo_free_data(data);
		return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}

static int	philo_run_threads(t_philo_data *data)
{
	PHILO_ASSERT(data != NULL);
	PHILO_ASSERT(data->params != NULL);
	PHILO_ASSERT(data->params[0] > 0);
	int				i;
	pthread_t		threads[data->params[0]];

	data->start_time = philo_get_current_time();
	data->is_running = Philo_true;
	i = -1;
	while (++i < data->params[0])
	{
		PHILO_ASSERT(data->philozophers + i != NULL);
		data->philozophers[i].last_eat_time = data->start_time;
		if (pthread_create(threads + i, NULL, philo_run, (void*)(data->philozophers + i)) != 0)
			PHILO_ERROR_RETURN(PHILO_FAILURE, "Cannot create thread %d\n", i);
	}
	philo_main_thread(data);
	i = -1;
	while (++i < data->params[0])
		if (pthread_join(threads[i], NULL) != 0)
			PHILO_ERROR_RETURN(PHILO_FAILURE, "Cannot join thread %d\n", i);
	return (PHILO_SUCCESS);
}

int			main(int argc, char **argv)
{
	t_philo_data	data;
	int				res;

	if (philo_init(argc, argv, &data) == PHILO_FAILURE)
		return (EXIT_FAILURE);
	res = philo_run_threads(&data);
	philo_free_data(&data);
	if (res == PHILO_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
