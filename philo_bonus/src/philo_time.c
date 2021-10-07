/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 10:28:38 by marvin            #+#    #+#             */
/*   Updated: 2021/10/01 10:28:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo_error.h"
#include "philo.h"

#define MIN_SLEEP_TIME_MICROSECS 100

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

unsigned long		philo_elapsed_time(void)
{
	static unsigned long	start = 0;

	if (!start)
		start = philo_get_current_time();
	return ((philo_get_current_time() - start));
}

int					philo_smart_sleep(t_philo_bool *is_running, unsigned long sleep_time_ms)
{
	int				res;
	unsigned long	start_time;
	unsigned long	current_time;

	start_time = philo_elapsed_time();
	current_time = start_time;
	while (sleep_time_ms > (current_time - start_time) && *is_running == Philo_true)
	{
		if((res = usleep(MIN_SLEEP_TIME_MICROSECS)) != 0)
			PHILO_ERROR("Error in usleep");
		PHILO_ASSERT(res == 0);
		if (res != 0)
			return (PHILO_FAILURE);
		current_time = philo_elapsed_time();
	}
	return (PHILO_SUCCESS);
}
