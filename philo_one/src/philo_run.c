/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 22:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2021/06/06 21:51:32 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	int	lock_res;

	ASSERT(philo != NULL);
	ASSERT(philo->data != NULL);
	ASSERT(philo->data->forks != NULL);
	ASSERT(philo->left_fork >= 0);
	ASSERT(philo->right_fork >= 0);
	lock_res = pthread_mutex_lock(philo->data->forks + philo->left_fork);//add protect
	ASSERT(lock_res == 0);
	philo_print_action(PHILO_TAKE_FORK, philo);
	lock_res = pthread_mutex_lock(philo->data->forks + philo->right_fork);// add protect
	ASSERT(lock_res == 0);
	philo_print_action(PHILO_TAKE_FORK, philo);
	philo->last_eat_time = philo_get_current_time();
	philo_print_action(PHILO_EATING, philo);
	ASSERT(philo->data->params[2] >= 0);
	usleep(philo->data->params[2] * 1000);
	lock_res = pthread_mutex_unlock(philo->data->forks + philo->left_fork);// add protect
	ASSERT(lock_res == 0);
	lock_res = pthread_mutex_unlock(philo->data->forks + philo->right_fork); // add protect
	ASSERT(lock_res == 0);
	++philo->number_of_eatings;
}

static void	philo_sleep(t_philo *philo)
{
	int	res;

	ASSERT(philo != NULL);
	philo_print_action(PHILO_SLEEPING, philo);
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
	while (Philo_true)
	{
		philo_eat(philo);
		// if (philo->data->params[4]
		// 	&& philo->number_of_eatings >= philo->data->params[4])
		// 	break;
		philo_sleep(philo);
		philo_think(philo);
		// check https://git.hexanyn.fr/42/philosophers/-/blob/master/philo_one/srcs/thread.c#L79
	}
	return (NULL);
}
