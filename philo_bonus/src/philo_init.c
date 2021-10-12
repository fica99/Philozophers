/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:38:43 by aashara-          #+#    #+#             */
/*   Updated: 2021/10/10 18:17:05 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo.h"

static int	philo_init_params(int argc, char **argv, int *params)
{
	int	i;

	if (argc != PHILO_MAX_NB_ARGS - 1 && argc != PHILO_MAX_NB_ARGS)
	{
		fprintf(stderr, "Invalid number of arguments\n");
		return (PHILO_FAILURE);
	}
	memset((void *)params, 0, sizeof(int) * PHILO_MAX_NB_ARGS);
	i = 0;
	while (++i < argc)
	{
		if (philo_is_int(argv[i]) == Philo_true)
			params[i - 1] = philo_atoi(argv[i]);
		else
		{
			fprintf(stderr, "Invalid argument: %s\n", argv[i]);
			return (PHILO_FAILURE);
		}
	}
	return (PHILO_SUCCESS);
}

static int	philo_validate_params(int argc, int *params)
{
	if (params[0] <= PHILO_MIN_NB_PHILO)
		fprintf(stderr, "Wrong parameter! %s must be > %d.\n",
		PHILO_NB_PHILO, PHILO_MIN_NB_PHILO);
	else if (params[1] <= PHILO_MIN_TIME_TO_DIE)
		fprintf(stderr, "Wrong parameter! %s must be > %d ms.\n",
		PHILO_TIME_TO_DIE, PHILO_MIN_TIME_TO_DIE);
	else if (params[2] <= PHILO_MIN_TIME_TO_EAT)
		fprintf(stderr, "Wrong parameter! %s must be > %d ms.\n",
		PHILO_TIME_TO_EAT, PHILO_MIN_TIME_TO_EAT);
	else if (params[3] <= PHILO_MIN_TIME_TO_SLEEP)
		fprintf(stderr, "Wrong parameter! %s must be > %d ms.\n",
		PHILO_TIME_TO_SLEEP, PHILO_MIN_TIME_TO_SLEEP);
	else if (argc == PHILO_MAX_NB_ARGS && params[4] <= PHILO_MIN_NB_EATINGS)
		fprintf(stderr, "Wrong parameter! %s must be > %d.\n",
		PHILO_NB_EATINGS, PHILO_MIN_NB_EATINGS);
	else
		return (PHILO_SUCCESS);
	return (PHILO_FAILURE);
}

static int	philo_init_data(t_philo_data *data)
{
	int		i;
	char	name[PHILO_SEM_MAX_LENGTH_NAME];

	data->philozophers = (t_philo *)malloc(sizeof(t_philo) * data->par[0]);
	if (!data->philozophers)
	{
		fprintf(stderr, "Cannot allocate memory\n");
		return (PHILO_FAILURE);
	}
	if (philo_sem_open(&data->sem_forks, PHILO_SEM_FORKS, data->par[0]) != PHILO_SUCCESS
		|| philo_sem_open(&data->sem_writing, PHILO_SEM_WRITING, 1) != PHILO_SUCCESS)
		return (PHILO_FAILURE);
	i = -1;
	while (++i < data->par[0])
	{
		memset((void *)(data->philozophers + i), 0, sizeof(t_philo));
		data->philozophers[i].id = i + 1;
		data->philozophers[i].data = data;
		if (philo_sem_open(&data->philozophers[i].sem_eating,
			philo_sem_name(PHILO_SEM_EATING, name, i), 1) != PHILO_SUCCESS)
			return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}

int	philo_init(int argc, char **argv, t_philo_data *data)
{
	memset((void *)data, 0, sizeof(t_philo_data));
	if (philo_init_params(argc, argv, data->par) == PHILO_FAILURE
		|| philo_validate_params(argc, data->par) == PHILO_FAILURE)
	{
		fprintf(stderr, "\nUsage\n  %s %s %s %s %s [%s]\n", argv[0],
			PHILO_NB_PHILO, PHILO_TIME_TO_DIE, PHILO_TIME_TO_EAT,
			PHILO_TIME_TO_SLEEP, PHILO_NB_EATINGS);
		return (PHILO_FAILURE);
	}
	if (philo_init_data(data) == PHILO_FAILURE)
	{
		fprintf(stderr, "Error in data initialization\n");
		return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}
