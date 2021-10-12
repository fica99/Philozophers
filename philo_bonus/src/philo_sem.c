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

char	*philo_sem_name(char const *base, char *buffer, int position)
{
	size_t	i;

	i = 0;
	while (base[i] != '\0')
	{
		buffer[i] = base[i];
		++i;
	}
	while (position > 0)
	{
		buffer[i++] = (position % 10) + '0';
		position /= 10;
	}
	buffer[i] = 0;
	return (buffer);
}

int	philo_sem_close(sem_t **sem, const char *name)
{
	sem_unlink(name);
	if (sem_close(*sem) == PHILO_FAILURE)
	{
		fprintf(stderr, "Cannot close semaphore\n");
		return (PHILO_FAILURE);
	}
	*sem = NULL;
	return (PHILO_SUCCESS);
}

int	philo_sem_open(sem_t **sem, const char *name, unsigned int value)
{
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT, S_IRWXU, value);
	if (*sem == NULL)
	{
		fprintf(stderr, "Cannot open semaphore\n");
		return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}

int	philo_sem_wait(sem_t *sem)
{
	if (sem_wait(sem) != PHILO_SUCCESS)
	{
		fprintf(stderr, "Error in sem_wait\n");
		return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}

int	philo_sem_post(sem_t *sem)
{
	if (sem_post(sem) != PHILO_SUCCESS)
	{
		fprintf(stderr, "Error in sem_post\n");
		return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}
