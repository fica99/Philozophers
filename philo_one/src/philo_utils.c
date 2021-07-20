/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:20:04 by aashara-          #+#    #+#             */
/*   Updated: 2021/06/06 21:33:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo_error.h"
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

	PHILO_ASSERT(str != NULL);
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

unsigned long		philo_get_current_time(void)
{
	struct timeval	tv;
	unsigned long	i;
	int				res;

	if ((res = gettimeofday(&tv, NULL)) != 0)
		PHILO_ERROR("Error in gettimeofday");
	PHILO_ASSERT(res == 0);
	i = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (i);
}

void			philo_print_action(t_philo_actions action, t_philo *philo)
{
	unsigned long			time_from_start;
	char					*text;

	PHILO_ASSERT(philo != NULL);
	PHILO_ASSERT(philo->data != NULL);
	if (philo->data->is_running == Philo_false)
		return ;
	time_from_start = philo_get_current_time() - philo->data->start_time;
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
	PHILO_LOCK(&philo->data->mutex_writing);
	printf("%lu\t %d %s\n", time_from_start, philo->number, text);
	PHILO_UNLOCK(&philo->data->mutex_writing);
}
