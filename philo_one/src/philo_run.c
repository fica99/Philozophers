/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 22:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2021/07/18 23:51:13 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo_error.h"
#include "philo.h"

static int	philo_eat(t_philo *philo)
{
	int	res;

	PHILO_ASSERT(philo != NULL);
	PHILO_ASSERT(philo->data != NULL);
	PHILO_ASSERT(philo->data->forks != NULL);
	if (pthread_mutex_lock(philo->data->forks + philo->left_fork) != 0)
		PHILO_ERROR_RETURN(PHILO_FAILURE, "Error in pthread_mutex_lock\n");
	philo_print_action(PHILO_TAKE_FORK, philo);
	if (pthread_mutex_lock(philo->data->forks + philo->right_fork) != 0)
		PHILO_ERROR_RETURN(PHILO_FAILURE, "Error in pthread_mutex_lock\n");
	philo_print_action(PHILO_TAKE_FORK, philo);
	philo->last_eat_time = philo_get_current_time();
	philo_print_action(PHILO_EATING, philo);
	if((res = usleep(philo->data->params[2] * 1000)) != 0)
		PHILO_ERROR("Error in usleep");
	PHILO_ASSERT(res == 0);
	if (pthread_mutex_unlock(philo->data->forks + philo->left_fork) != 0)
		PHILO_ERROR_RETURN(PHILO_FAILURE, "Error in pthread_mutex_unlock\n");
	if (pthread_mutex_unlock(philo->data->forks + philo->right_fork) != 0)
		PHILO_ERROR_RETURN(PHILO_FAILURE, "Error in pthread_mutex_unlock\n");
	++philo->number_of_eatings;
	return (PHILO_SUCCESS);
}

static void	philo_sleep(t_philo *philo)
{
	int	res;

	PHILO_ASSERT(philo != NULL);
	philo_print_action(PHILO_SLEEPING, philo);
	PHILO_ASSERT(philo->data != NULL);
	PHILO_ASSERT(philo->data->params != NULL);
	PHILO_ASSERT(philo->data->params[3] >= 0);
	if((res = usleep(philo->data->params[3] * 1000)) != 0)
		PHILO_ERROR("Error in usleep");
	PHILO_ASSERT(res == 0);
}

static void philo_think(t_philo *philo)
{
	PHILO_ASSERT(philo != NULL);
	philo_print_action(PHILO_THINKING, philo);
}

void		*philo_run(void *philo_ptr)
{
	t_philo			*philo;

	PHILO_ASSERT(philo_ptr != NULL);
	philo = philo_ptr;
	PHILO_ASSERT(philo->data != NULL);
	while (philo->data->is_running == Philo_true)
	{
		if (philo_eat(philo) == PHILO_FAILURE)
			return (NULL);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}


void			philo_main_thread(t_philo_data *data)
{
	PHILO_ASSERT(data != NULL);
	int	i;

	while (Philo_true)
	{
		i = -1;
		PHILO_ASSERT(data->params != NULL);
		while (++i < data->params[0])
		{
			PHILO_ASSERT(data->philozophers + i != NULL);
			PHILO_ASSERT(data->params[1] >= 0);
			if (data->philozophers[i].last_eat_time + data->params[1] < philo_get_current_time())
			{
				data->is_running = Philo_false;
				philo_print_action(PHILO_DIED, data->philozophers + i);
				return;
			}
		}
	}
}
