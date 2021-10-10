/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 22:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2021/10/10 18:17:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo.h"

#define PHILO_THREADS_DELAY 100
#define PHILO_MONITOR_DELAY 100

static int	philo_eat(t_philo *philo)
{
	int	res;
	int	min;
	int	max;

	min = ft_min(philo->id - 1, philo->id % philo->data->par[0]);
	max = ft_max(philo->id - 1, philo->id % philo->data->par[0]);
	philo_mutex_lock(philo->data->forks + min);
	philo_print_action(PHILO_TAKE_FORK, philo);
	philo_mutex_lock(philo->data->forks + max);
	philo_print_action(PHILO_TAKE_FORK, philo);
	philo_mutex_lock(&philo->mutex_eating);
	philo->last_eat_time = philo_elapsed_time();
	++philo->nb_eat;
	philo_print_action(PHILO_EATING, philo);
	res = philo_smart_sleep(philo->data, philo->data->par[2]);
	philo_mutex_unlock(&philo->mutex_eating);
	philo_mutex_unlock(philo->data->forks + max);
	philo_mutex_unlock(philo->data->forks + min);
	return (res);
}

static void	*philo_run(void *philo_ptr)
{
	t_philo	*philo;

	philo = philo_ptr;
	while (philo_is_running(philo->data) == Philo_true)
	{
		if (philo_eat(philo) == PHILO_FAILURE)
			break ;
		philo_print_action(PHILO_SLEEPING, philo);
		if (philo_smart_sleep(philo->data, philo->data->par[3])
			== PHILO_FAILURE)
			break ;
		philo_print_action(PHILO_THINKING, philo);
	}
	return (NULL);
}

static void	philo_monitor(t_philo_data *data)
{
	int				i;
	t_philo_bool	is_eated;

	while (philo_is_running(data) == Philo_true)
	{
		is_eated = Philo_true;
		i = -1;
		while (++i < data->par[0])
		{
			philo_mutex_lock(&data->philozophers[i].mutex_eating);
			if (data->philozophers[i].last_eat_time + data->par[1]
				< philo_elapsed_time())
			{
				philo_print_action(PHILO_DIED, data->philozophers + i);
				philo_mutex_unlock(&data->philozophers[i].mutex_eating);
				return ;
			}
			philo_mutex_unlock(&data->philozophers[i].mutex_eating);
			if (!data->par[4] || data->philozophers[i].nb_eat < data->par[4])
				is_eated = Philo_false;
		}
		philo_set_is_running(data, !is_eated);
		if (usleep(PHILO_MONITOR_DELAY) != 0)
			fprintf(stderr, "Error in usleep");
	}
}

int	philo_run_threads(t_philo_data *data)
{
	int				i;

	philo_set_is_running(data, Philo_true);
	i = -1;
	while (++i < data->par[0])
	{
		if (pthread_create(&(data->philozophers[i].tid), NULL, philo_run,
				(void*)(data->philozophers + i)) != 0)
		{
			fprintf(stderr, "Cannot create thread %d\n", i);
			return (PHILO_FAILURE);
		}
		if (usleep(PHILO_THREADS_DELAY) != 0)
			fprintf(stderr, "Error in usleep");
	}
	philo_monitor(data);
	while (--i >= 0)
	{
		if (pthread_join(data->philozophers[i].tid, NULL) != 0)
		{
			fprintf(stderr, "Cannot join thread %d\n", i);
			return (PHILO_FAILURE);
		}
	}
	return (PHILO_SUCCESS);
}
