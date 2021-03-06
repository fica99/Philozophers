/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:20:04 by aashara-          #+#    #+#             */
/*   Updated: 2021/10/13 11:26:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo.h"

#define MAX_INT_LENGTH 10

static t_philo_bool	philo_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (Philo_true);
	return (Philo_false);
}

static t_philo_bool	philo_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

t_philo_bool	philo_is_int(const char *str)
{
	int						sign;
	size_t					i;
	long long				res;

	i = 0;
	while (philo_isspace(str[i]))
		++i;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	str += i;
	i = 0;
	res = 0;
	while (philo_isdigit(str[i]) && i < MAX_INT_LENGTH)
		res = res * 10 + str[i++] - '0';
	res *= sign;
	if (res > INT_MAX || res < INT_MIN)
		return (Philo_false);
	while (philo_isspace(str[i]))
		++i;
	return ((t_philo_bool)(str[i] == '\0'));
}

int	philo_atoi(const char *str)
{
	int						sign;
	size_t					i;
	long long				res;

	i = 0;
	while (philo_isspace(str[i]))
		++i;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	str += i;
	i = 0;
	res = 0;
	while (philo_isdigit(str[i]))
		res = res * 10 + str[i++] - '0';
	res *= sign;
	return ((int)res);
}

void	philo_print_action(t_philo_actions action, t_philo *philo)
{
	unsigned long			time_from_start;
	char					*text;

	text = "";
	if (action == PHILO_EATING)
		text = PHILO_EATING_TEXT;
	else if (action == PHILO_SLEEPING)
		text = PHILO_SLEEPING_TEXT;
	else if (action == PHILO_THINKING)
		text = PHILO_THINKING_TEXT;
	else if (action == PHILO_TAKE_FORK)
		text = PHILO_TAKE_FORK_TEXT;
	else if (action == PHILO_DIED)
		text = PHILO_DIED_TEXT;
	philo_sem_wait(philo->data->sem_writing);
	time_from_start = philo_elapsed_time();
	printf("%lu %d %s\n", time_from_start, philo->id, text);
	if (action == PHILO_DIED)
		exit(EXIT_SUCCESS);
	philo_sem_post(philo->data->sem_writing);
}
