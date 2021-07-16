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
#include "philo.h"

static t_philo_bool	philo_is_valid_arg(const char *str)
{
	size_t				i;
	long long			rez;

	ASSERT(str != NULL);
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

int					philo_init_params(int argc, char **argv, int params[6])
{
	int	i;

	ASSERT(params != NULL);
	ASSERT(argv != NULL);
	if (argc != 5 && argc != 6)
	{
		dprintf(2, "Invalid number of arguments\n");
		return (PHILO_FAILURE);
	}
	memset((void*)params, 0, sizeof(int) * 6);
	i = 0;
	while (++i < argc)
	{
		ASSERT(argv[i] != NULL);
		if (philo_is_valid_arg(argv[i]) == Philo_true)
			params[i - 1] = philo_atoi(argv[i]);
		else
		{
			dprintf(2, "Invalid argument: %s\n", argv[i]);
			return (PHILO_FAILURE);
		}
	}
	return (PHILO_SUCCESS);
}

int					philo_validate_params(int params[6])
{
	ASSERT(params != NULL);
	if (params[0] < PHILO_MIN_NB_PHILO)
		dprintf(2, "Wrong parameter: number_of_philosophers\n");
	else if (params[1] < PHILO_MIN_TIME_TO_DIE)
		dprintf(2, "Wrong parameter: time_to_die\n");
	else if (params[2] < PHILO_MIN_TIME_TO_EAT)
		dprintf(2, "Wrong parameter: time_to_eat\n");
	else if (params[3] < PHILO_MIN_TIME_TO_SLEEP)
		dprintf(2, "Wrong parameter: time_to_sleep\n");
	else if (params[4] < PHILO_MIN_NB_EATINGS)
		dprintf(2, "Wrong parameter: number_of_times_each_philosopher_must_eat\n");
	else
		return (PHILO_SUCCESS);
	return (PHILO_FAILURE);
}
