/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:38:43 by aashara-          #+#    #+#             */
/*   Updated: 2021/10/10 14:17:34 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo_error.h"
#include "philo.h"

static int			philo_init_params(int argc, char **argv, int *params)
{
	int	i;

	if (argc != PHILO_MAX_NB_ARGS - 1 && argc != PHILO_MAX_NB_ARGS)
		PHILO_ERROR_RETURN(PHILO_FAILURE, "Invalid number of arguments\n");
	memset((void*)params, 0, sizeof(int) * PHILO_MAX_NB_ARGS);
	i = 0;
	while (++i < argc)
	{
		if (philo_is_int(argv[i]) == Philo_true)
			params[i - 1] = philo_atoi(argv[i]);
		else
			PHILO_ERROR_RETURN(PHILO_FAILURE, "Invalid argument: %s\n", argv[i]);
	}
	return (PHILO_SUCCESS);
}

static int			philo_validate_params(int argc, int *params)
{
	if (params[0] < PHILO_MIN_NB_PHILO || params[0] > PHILO_MAX_NB_PHILO)
		PHILO_ERROR("Wrong parameter! %s must be not less then %d and not greater then %d.\n", PHILO_NB_PHILO, PHILO_MIN_NB_PHILO, PHILO_MAX_NB_PHILO);
	else if (params[1] < PHILO_MIN_TIME_TO_DIE)
		PHILO_ERROR("Wrong parameter! %s must be not less then %d ms.\n", PHILO_TIME_TO_DIE, PHILO_MIN_TIME_TO_DIE);
	else if (params[2] < PHILO_MIN_TIME_TO_EAT)
		PHILO_ERROR("Wrong parameter! %s must be not less then %d ms.\n", PHILO_TIME_TO_EAT, PHILO_MIN_TIME_TO_EAT);
	else if (params[3] < PHILO_MIN_TIME_TO_SLEEP)
		PHILO_ERROR("Wrong parameter! %s must be not less then %d ms.\n", PHILO_TIME_TO_SLEEP, PHILO_MIN_TIME_TO_SLEEP);
	else if (argc == PHILO_MAX_NB_ARGS && params[4] < PHILO_MIN_NB_EATINGS)
		PHILO_ERROR("Wrong parameter! %s must be not less then %d.\n", PHILO_NB_EATINGS, PHILO_MIN_NB_EATINGS);
	else
		return (PHILO_SUCCESS);
	return (PHILO_FAILURE);
}


static int			philo_init_data(t_philo_data *data)
{
	int	i;

	if (!(data->philozophers = (t_philo*)malloc(sizeof(t_philo) *
				data->params[0])) ||
		!(data->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) *
				data->params[0])))
		PHILO_ERROR_RETURN(PHILO_FAILURE, "Cannot allocate memory\n");
	if (pthread_mutex_init(&data->mutex_writing, NULL))
		PHILO_ERROR_RETURN(PHILO_FAILURE, "Cannot init mutex writing\n");
	if (pthread_mutex_init(&data->mutex_is_running, NULL))
		PHILO_ERROR_RETURN(PHILO_FAILURE, "Cannot init mutex is running\n");
	i = -1;
	while (++i < data->params[0])
	{
		memset((void*)(data->philozophers + i), 0, sizeof(t_philo));
		data->philozophers[i].id = i + 1;
		data->philozophers[i].data = data;
		if (pthread_mutex_init(&data->philozophers[i].mutex_eating, NULL))
			PHILO_ERROR_RETURN(PHILO_FAILURE, "Cannot init mutex eating\n");
		if (pthread_mutex_init(data->forks + i, NULL))
			PHILO_ERROR_RETURN(PHILO_FAILURE, "Cannot init mutexes for forks\n");
	}
	return (PHILO_SUCCESS);
}

int					philo_init(int argc, char **argv, t_philo_data *data)
{
	memset((void*)data, 0, sizeof(t_philo_data));
	if (philo_init_params(argc, argv, data->params) == PHILO_FAILURE
	|| philo_validate_params(argc, data->params) == PHILO_FAILURE)
		PHILO_ERROR_RETURN(PHILO_FAILURE, "\nUsage\n  %s %s %s %s %s [%s]\n", argv[0], PHILO_NB_PHILO,
		PHILO_TIME_TO_DIE, PHILO_TIME_TO_EAT, PHILO_TIME_TO_SLEEP, PHILO_NB_EATINGS);
	if (philo_init_data(data) == PHILO_FAILURE)
	{
		PHILO_ERROR("Error in data initialization\n");
		philo_free_data(data);
		return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}
