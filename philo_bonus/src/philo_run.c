/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 22:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2021/10/13 09:45:39 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo.h"

#define PHILO_THREADS_DELAY 100
#define PHILO_MONITOR_DELAY 100

static int	philo_eat(t_philo *philo)
{
	int	res;

	philo_sem_wait(philo->data->sem_forks);
	philo_print_action(PHILO_TAKE_FORK, philo);
	philo_sem_wait(philo->data->sem_forks);
	philo_sem_wait(philo->sem_eating);
	philo_print_action(PHILO_TAKE_FORK, philo);
	philo->last_eat_time = philo_elapsed_time();
	++philo->nb_eat;
	philo_print_action(PHILO_EATING, philo);
	res = philo_smart_sleep(philo->data->par[2]);
	philo_sem_post(philo->sem_eating);
	philo_sem_post(philo->data->sem_forks);
	philo_sem_post(philo->data->sem_forks);
	return (res);
}

static void	*philo_monitor(void *philo_ptr)
{
	t_philo			*philo;
	t_philo_bool	is_eated;

	philo = (t_philo *)philo_ptr;
	while (Philo_true)
	{
		is_eated = Philo_true;
		philo_sem_wait(philo->sem_eating);
		if (philo->last_eat_time + philo->data->par[1] < philo_elapsed_time())
		{
			philo_print_action(PHILO_DIED, philo);
			philo_sem_post(philo->sem_eating);
		}
		philo_sem_post(philo->sem_eating);
		if (!philo->data->par[4] || philo->nb_eat < philo->data->par[4])
			is_eated = Philo_false;
		if (is_eated)
			exit(EXIT_SUCCESS);
		if (usleep(PHILO_MONITOR_DELAY) != 0)
			fprintf(stderr, "Error in usleep");
	}
}

static int	philo_run(t_philo *philo)
{
	pthread_t	tid;

	if (pthread_create(&tid, NULL, philo_monitor, (void *)(philo))
		== PHILO_FAILURE)
	{
		fprintf(stderr, "Cannot create thread philo_monitor\n");
		return (PHILO_FAILURE);
	}
	if (pthread_detach(tid) == PHILO_FAILURE)
	{
		fprintf(stderr, "Cannot detach philo_monitor thread\n");
		return (PHILO_FAILURE);
	}
	while (Philo_true)
	{
		if (philo_eat(philo) == PHILO_FAILURE)
			break ;
		philo_print_action(PHILO_SLEEPING, philo);
		if (philo_smart_sleep(philo->data->par[3])
			== PHILO_FAILURE)
			break ;
		philo_print_action(PHILO_THINKING, philo);
	}
	return (PHILO_FAILURE);
}

static void	philo_create_processes(t_philo_data *data)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < data->par[0])
	{
		pid = fork();
		if (pid == PHILO_FAILURE)
			fprintf(stderr, "Cannot create process %d\n", i);
		else if (pid == 0)
		{
			philo_run(data->philozophers + i);
			exit(EXIT_FAILURE);
		}
		else
			data->philozophers[i].pid = pid;
	}
}

int	philo_run_processes(t_philo_data *data)
{
	int		i;
	pid_t	pid;
	int		status;

	philo_create_processes(data);
	pid = waitpid(-1, &status, 0);
	if (pid == PHILO_FAILURE)
	{
		fprintf(stderr, "Error in waitpid %d\n", status);
	}
	i = -1;
	while (++i < data->par[0])
	{
		if (pid != data->philozophers[i].pid)
		{
			if (kill(data->philozophers[i].pid, SIGQUIT) == PHILO_FAILURE)
				fprintf(stderr, "Cannot kill process %d\n",
					data->philozophers[i].pid);
		}
	}
	return (PHILO_SUCCESS);
}
