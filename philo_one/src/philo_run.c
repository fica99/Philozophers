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

// static void	philo_eat(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->data->forks + philo->left_fork);
// 	philo_print_action(PHILO_TAKE_FORK, philo);
// 	pthread_mutex_lock(philo->data->forks + philo->right_fork);
// 	philo_print_action(PHILO_TAKE_FORK, philo);
// 	philo->last_eat_time = philo_get_current_time();
// 	philo_print_action(PHILO_EATING, philo);
// 	usleep(philo->data->params[2] * 1000);
// 	pthread_mutex_unlock(philo->data->forks + philo->left_fork);
// 	pthread_mutex_unlock(philo->data->forks + philo->right_fork);
// 	++philo->number_of_eatings;
// }

// static void	philo_sleep(t_philo *philo)
// {
// 	philo_print_action(PHILO_SLEEPING, philo);
// 	usleep(philo->data->params[3] * 1000);
// }

void		*philo_run(void *philo_ptr)
{
	t_philo			*philo;

	philo = philo_ptr;
	while (Philo_true)
	{
		printf("%p\n", philo->data);
		// philo_eat(philo);
		// if (philo->data->params[4]
		// 	&& philo->number_of_eatings >= philo->data->params[4])
		// 	break;
		// philo_sleep(philo);
		// philo_print_action(PHILO_THINKING, philo);
	}
	return (NULL);
}
