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
#include "philo.h"

static int	philo_eat(t_philo *philo)
{
	ASSERT(philo != NULL);
	ASSERT(philo->data != NULL);
	ASSERT(philo->data->forks != NULL);
	ASSERT(philo->left_fork >= 0);
	ASSERT(philo->right_fork >= 0);
	if (pthread_mutex_lock(philo->data->forks + philo->left_fork) != 0)
		return (PHILO_FAILURE);
	philo_print_action(PHILO_TAKE_FORK, philo);
	if (pthread_mutex_lock(philo->data->forks + philo->right_fork) != 0)
		return (PHILO_FAILURE);
	philo_print_action(PHILO_TAKE_FORK, philo);
	philo->last_eat_time = philo_get_current_time();
	philo_print_action(PHILO_EATING, philo);
	ASSERT(philo->data->params[2] >= 0);
	usleep(philo->data->params[2] * 1000);
	if (pthread_mutex_unlock(philo->data->forks + philo->left_fork) != 0)
		return (PHILO_FAILURE);
	if (pthread_mutex_unlock(philo->data->forks + philo->right_fork) != 0)
		return (PHILO_FAILURE);
	++philo->number_of_eatings;
	return (PHILO_SLEEPING);
}

static void	philo_sleep(t_philo *philo)
{
	int	res;

	ASSERT(philo != NULL);
	philo_print_action(PHILO_SLEEPING, philo);
	ASSERT(philo->data != NULL);
	ASSERT(philo->data->params != NULL);
	ASSERT(philo->data->params[3] >= 0);
	res = usleep(philo->data->params[3] * 1000); // add protect
	ASSERT(res == 0);
}

static void philo_think(t_philo *philo)
{
	ASSERT(philo != NULL);
	philo_print_action(PHILO_THINKING, philo);
}

void		*philo_run(void *philo_ptr)
{
	t_philo			*philo;

	ASSERT(philo_ptr != NULL);
	philo = philo_ptr;
	while (philo->data->is_running == Philo_true)
	{
		if (philo_eat(philo) == PHILO_FAILURE)
		{
			dprintf(2, "Error occured while lock and unlock mutexes\n");
			return (NULL);
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}


void			philo_main_thread(t_philo_data *data)
{
	ASSERT(data != NULL);
	int	i;

	while (Philo_true)
	{
		i = -1;
		while (++i < data->params[0])
		{
			if (data->philozophers[i].last_eat_time + data->params[1] < philo_get_current_time())
			{
				philo_print_action(PHILO_DIED, data->philozophers + i);
				return;
			}
		}
	}
}
