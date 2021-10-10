/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 22:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2021/10/10 14:16:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo_error.h"
#include "philo.h"

# define PHILO_THREADS_DELAY 100

static int	philo_eat(t_philo *philo)
{
	int	res;
	int	min;
	int	max;

	min = FT_MIN(philo->id - 1, philo->data->params[0] <= philo->id ? 0 : philo->id);
	PHILO_ASSERT(philo->data->forks + min ! NULL);
	PHILO_MUTEX_LOCK(philo->data->forks + min);
	philo_print_action(PHILO_TAKE_FORK, philo);
	max = FT_MAX(philo->id - 1, philo->data->params[0] <= philo->id ? 0 : philo->id);
	PHILO_ASSERT(philo->data->forks + max ! NULL);
	PHILO_MUTEX_LOCK(philo->data->forks + max);
	philo_print_action(PHILO_TAKE_FORK, philo);
	PHILO_MUTEX_LOCK(&philo->mutex_eating);
	philo->last_eat_time = philo_elapsed_time();
	++philo->number_of_eatings;
	philo_print_action(PHILO_EATING, philo);
	res = philo_smart_sleep(philo->data, philo->data->params[2]);
	PHILO_MUTEX_UNLOCK(&philo->mutex_eating);
	PHILO_MUTEX_UNLOCK(philo->data->forks + max);
	PHILO_MUTEX_UNLOCK(philo->data->forks + min);
	return (res);
}

static void	*philo_run(void *philo_ptr)
{
	t_philo	*philo;

	philo = philo_ptr;
	while (philo_is_running(philo->data) == Philo_true)
	{
		if (philo_eat(philo) == PHILO_FAILURE)
			break;
		philo_print_action(PHILO_SLEEPING, philo);
		if (philo_smart_sleep(philo->data, philo->data->params[3]) == PHILO_FAILURE)
			break;
		philo_print_action(PHILO_THINKING, philo);
	}
	return (NULL);
}

static void	philo_monitor(t_philo_data *data)
{
	int				i;
	t_philo_bool	is_eated;

	PHILO_ASSERT(data != NULL);
	while (philo_is_running(data) == Philo_true)
	{
		is_eated = Philo_true;
		i = -1;
		while (++i < data->params[0])
		{
			PHILO_ASSERT(data->philozophers + i != NULL);
			PHILO_MUTEX_LOCK(&data->philozophers[i].mutex_eating);
			if (data->philozophers[i].last_eat_time + data->params[1] < philo_elapsed_time())
			{
				philo_print_action(PHILO_DIED, data->philozophers + i);
				PHILO_MUTEX_UNLOCK(&data->philozophers[i].mutex_eating);
				return ;
			}
			PHILO_MUTEX_UNLOCK(&data->philozophers[i].mutex_eating);
			if (data->params[4] == 0 ||
				data->philozophers[i].number_of_eatings < data->params[4])
				is_eated = Philo_false;
		}
		philo_set_is_running(data, !is_eated);
	}
}

int			philo_run_threads(t_philo_data *data)
{
	int				i;
	int				res;
	pthread_t		threads[data->params[0]];

	philo_set_is_running(data, Philo_true);
	i = -1;
	while (++i < data->params[0])
	{
		PHILO_ASSERT(data->philozophers + i != NULL);
		if (pthread_create(threads + i, NULL, philo_run, (void*)(data->philozophers + i)) != 0)
			PHILO_ERROR_RETURN(PHILO_FAILURE, "Cannot create thread %d\n", i);
		if((res = usleep(PHILO_THREADS_DELAY)) != 0)
			PHILO_ERROR("Error in usleep");
		PHILO_ASSERT(res == 0);
	}
	philo_monitor(data);
	while (--i >= 0)
		if (pthread_join(threads[i], NULL) != 0)
			PHILO_ERROR_RETURN(PHILO_FAILURE, "Cannot join thread %d\n", i);
	return (PHILO_SUCCESS);
}
