/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:46:14 by aashara-          #+#    #+#             */
/*   Updated: 2021/10/10 16:15:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo.h"

int	philo_mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) != PHILO_SUCCESS)
	{
		fprintf(stderr, "Cannot destroy mutex\n");
		return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}

int	philo_mutex_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != PHILO_SUCCESS)
	{
		fprintf(stderr, "Cannot init mutex\n");
		return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}

int	philo_mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != PHILO_SUCCESS)
	{
		fprintf(stderr, "Error in pthread_mutex_lock\n");
		return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}

int	philo_mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != PHILO_SUCCESS)
	{
		fprintf(stderr, "Error in pthread_mutex_unlock\n");
		return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}
