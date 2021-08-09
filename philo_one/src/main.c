/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:49:22 by aashara-          #+#    #+#             */
/*   Updated: 2021/08/09 20:57:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo_error.h"
#include "philo.h"

void		philo_free_data(t_philo_data *data)
{
	int	i;

	PHILO_ASSERT(data != NULL);
	PHILO_ASSERT(data->philozophers != NULL);
	PHILO_ASSERT(data->params != NULL);
	if (data == NULL)
		return;
	if (data->philozophers != NULL)
		free(data->philozophers);
	if (pthread_mutex_destroy(&data->mutex_writing) != 0)
		PHILO_ERROR_RETURN(, "Cannot destroy mutex writing\n");
	if (pthread_mutex_destroy(&data->mutex_eating) != 0)
		PHILO_ERROR_RETURN(, "Cannot destroy mutex eating\n");
	i = -1;
	while (++i < data->params[0])
	{
		PHILO_ASSERT(data->forks + i != NULL);
		if (pthread_mutex_destroy(data->forks + i) != 0)
			PHILO_ERROR_RETURN(, "Cannot destroy forkes mutexes\n");
	}
	if (data->forks != NULL)
		free(data->forks);
}

static int	philo_run_threads(t_philo_data *data)
{
	PHILO_ASSERT(data != NULL);
	PHILO_ASSERT(data->params != NULL);
	int				i;
	pthread_t		threads[data->params[0]];

	data->start_time = philo_get_current_time();
	data->is_running = Philo_true;
	i = -1;
	while (++i < data->params[0])
	{
		PHILO_ASSERT(data->philozophers + i != NULL);
		data->philozophers[i].last_eat_time = philo_get_current_time();
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
