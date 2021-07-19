/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:38:43 by aashara-          #+#    #+#             */
/*   Updated: 2021/07/17 12:24:07 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo_error.h"
#include "philo.h"

static t_philo_bool	philo_is_valid_arg(const char *str)
{
	size_t				i;
	long long			rez;

	PHILO_ASSERT(str != NULL);
	if (str == NULL)
		return (Philo_false);
	i = 0;
	while (philo_isspace(str[i]))
		++i;
	str += i;
	i = 0;
	if (!(str[i] == '+' || philo_isdigit(str[i])))
		return (Philo_false);
	rez = 0;
	while (philo_isdigit(str[i]) && i < 12)
		rez = rez * 10 + str[i++] - '0';
	if (rez > INT_MAX || i > 11)
		return (Philo_false);
	while (philo_isspace(str[i]))
		++i;
	if (str[i] != '\0')
		return (Philo_false);
	return (Philo_true);
}

int					philo_init_params(int argc, char **argv, int params[PHILO_MAX_NB_ARGS])
{
	int	i;

	PHILO_ASSERT(params != NULL);
	PHILO_ASSERT(argv != NULL);
	if (argc != PHILO_MAX_NB_ARGS - 1 && argc != PHILO_MAX_NB_ARGS)
		PHILO_ERROR_RETURN(PHILO_FAILURE, "Invalid number of arguments\n");
	memset((void*)params, 0, sizeof(int) * PHILO_MAX_NB_ARGS);
	i = 0;
	while (++i < argc)
	{
		PHILO_ASSERT(argv[i] != NULL);
		if (philo_is_valid_arg(argv[i]) == Philo_true)
			params[i - 1] = philo_atoi(argv[i]);
		else
			PHILO_ERROR_RETURN(PHILO_FAILURE, "Invalid argument: %s\n", argv[i]);
	}
	return (PHILO_SUCCESS);
}

int					philo_validate_params(int params[PHILO_MAX_NB_ARGS])
{
	PHILO_ASSERT(params != NULL);
	if (params[0] < PHILO_MIN_NB_PHILO)
		PHILO_ERROR("Wrong parameter: %s\n", PHILO_NB_PHILO);
	else if (params[1] < PHILO_MIN_TIME_TO_DIE)
		PHILO_ERROR("Wrong parameter: %s\n", PHILO_TIME_TO_DIE);
	else if (params[2] < PHILO_MIN_TIME_TO_EAT)
		PHILO_ERROR("Wrong parameter: %s\n", PHILO_TIME_TO_EAT);
	else if (params[3] < PHILO_MIN_TIME_TO_SLEEP)
		PHILO_ERROR("Wrong parameter: %s\n", PHILO_TIME_TO_SLEEP);
	else if (params[4] < PHILO_MIN_NB_EATINGS)
		PHILO_ERROR("Wrong parameter: %s\n", PHILO_NB_EATINGS);
	else
		return (PHILO_SUCCESS);
	return (PHILO_FAILURE);
}
