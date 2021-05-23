/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:20:04 by aashara-          #+#    #+#             */
/*   Updated: 2021/05/23 21:41:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_bool	philo_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
	c == '\v')
		return (Philo_true);
	return (Philo_false);
}

t_philo_bool	philo_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int				philo_atoi(const char *str)
{
	int						sign;
	size_t					i;
	long long				rez;

	i = 0;
	while (philo_isspace(str[i]))
		++i;
	sign = 1;
	str += i;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	rez = 0;
	while (philo_isdigit(str[i]) && i < 12)
		rez = rez * 10 + str[i++] - '0';
	rez *= sign;
	return ((int)rez);
}

