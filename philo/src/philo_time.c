/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 10:28:38 by marvin            #+#    #+#             */
/*   Updated: 2021/10/10 16:41:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo.h"

#define MIN_SLEEP_TIME_MICROSECS 100

unsigned long	philo_get_current_time(void)
{
	struct timeval	tv;
	unsigned long	i;
	int				res;

	res = gettimeofday(&tv, NULL);
	if (res == PHILO_FAILURE)
		fprintf(stderr, "Error in gettimeofday");
	i = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (i);
}

unsigned long	philo_elapsed_time(void)
{
	static unsigned long	start = 0;

	if (!start)
		start = philo_get_current_time();
	return ((philo_get_current_time() - start));
}

int	philo_smart_sleep(t_philo_data *data, unsigned long sleep_time_ms)
{
	int				res;
	unsigned long	start_time;
	unsigned long	current_time;

	start_time = philo_elapsed_time();
	current_time = start_time;
	while (sleep_time_ms > (current_time - start_time)
		&& philo_is_running(data) == Philo_true)
	{
		res = usleep(MIN_SLEEP_TIME_MICROSECS);
		if (res == PHILO_FAILURE)
		{
			fprintf(stderr, "Error in usleep");
			return (PHILO_FAILURE);
		}
		current_time = philo_elapsed_time();
	}
	if (philo_is_running(data) == Philo_false)
		return (PHILO_FAILURE);
	return (PHILO_SUCCESS);
}
