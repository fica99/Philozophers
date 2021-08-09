/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 22:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2021/08/09 21:48:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo_error.h"
#include "philo.h"

#define MIN_SLEEP_TIME_MICROSECS 100

static int	philo_smart_sleep(t_philo_bool *is_running, unsigned long sleep_time_ms)
{
	int				res;
	unsigned long	start_time;
	unsigned long	current_time;

	start_time = philo_get_current_time();
	current_time = philo_get_current_time();
	while (sleep_time_ms > (current_time - start_time) && *is_running == Philo_true)
	{
		if((res = usleep(MIN_SLEEP_TIME_MICROSECS)) != 0)
			PHILO_ERROR("Error in usleep");
		PHILO_ASSERT(res == 0);
		if (res != 0)
			return (PHILO_FAILURE);
		current_time = philo_get_current_time();
	}
	return (PHILO_SUCCESS);
}

static int	philo_eat(t_philo *philo)
{
	int	res;

	PHILO_ASSERT(philo != NULL);
	PHILO_ASSERT(philo->data != NULL);
	PHILO_ASSERT(philo->data->forks != NULL);
	PHILO_LOCK(philo->data->forks +
		FT_MIN(philo->left_fork, philo->right_fork));
	philo_print_action(PHILO_TAKE_FORK, philo);
	PHILO_LOCK(philo->data->forks +
		FT_MAX(philo->left_fork, philo->right_fork));
	philo_print_action(PHILO_TAKE_FORK, philo);
	PHILO_LOCK(&philo->data->mutex_eating);
	philo->last_eat_time = philo_get_current_time();
	philo_print_action(PHILO_EATING, philo);
	res = philo_smart_sleep(&philo->data->is_running, philo->data->params[2]);
	PHILO_UNLOCK(&philo->data->mutex_eating);
	PHILO_UNLOCK(philo->data->forks +
		FT_MAX(philo->left_fork, philo->right_fork));
	PHILO_UNLOCK(philo->data->forks +
		FT_MIN(philo->left_fork, philo->right_fork));
	++philo->number_of_eatings;
	return (res);
}

void		*philo_run(void *philo_ptr)
{
	t_philo	*philo;

	PHILO_ASSERT(philo_ptr != NULL);
	philo = philo_ptr;
	PHILO_ASSERT(philo->data != NULL);
	while (philo->data->is_running == Philo_true)
	{
		PHILO_ASSERT(philo != NULL);
		PHILO_ASSERT(philo->data != NULL);
		PHILO_ASSERT(philo->data->params != NULL);
		if (philo_eat(philo) == PHILO_FAILURE)
			break;
		philo_print_action(PHILO_SLEEPING, philo);
		if (philo_smart_sleep(&philo->data->is_running, philo->data->params[3]) == PHILO_FAILURE)
			break;
		philo_print_action(PHILO_THINKING, philo);
	}
	return (NULL);
}


void		philo_main_thread(t_philo_data *data)
{
	int				i;
	t_philo_bool	is_eated;

	PHILO_ASSERT(data != NULL);
	while (data->is_running == Philo_true)
	{
		i = -1;
		PHILO_ASSERT(data->params != NULL);
		is_eated = Philo_true;
		while (++i < data->params[0])
		{
			PHILO_ASSERT(data->philozophers + i != NULL);
			PHILO_LOCK(&data->mutex_eating);
			if (data->philozophers[i].last_eat_time + data->params[1] < philo_get_current_time())
			{
				PHILO_UNLOCK(&data->mutex_eating);
				philo_print_action(PHILO_DIED, data->philozophers + i);
				data->is_running = Philo_false;
				return ;
			}
			PHILO_UNLOCK(&data->mutex_eating);
			if (data->params[4] == 0 ||
				data->philozophers[i].number_of_eatings < data->params[4])
				is_eated = Philo_false;
		}
		data->is_running = !is_eated;
	}
}
