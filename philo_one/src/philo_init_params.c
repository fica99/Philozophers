/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:38:43 by aashara-          #+#    #+#             */
/*   Updated: 2021/05/23 22:07:34 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo_bool	philo_is_valid_arg(const char *str)
{
	size_t				i;
	long long			rez;

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

	if (argc != 5 && argc != 6)
	{
		dprintf(2, "Invalid number of arguments\n");
		return (PHILO_FAILURE);
	}
	memset((void*)params, 0, sizeof(int) * 6);
	params[5] = -1;
	i = 0;
	while (++i < argc)
	{
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
