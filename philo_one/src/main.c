/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:49:22 by aashara-          #+#    #+#             */
/*   Updated: 2021/05/23 22:05:47 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

# define PHILO_ARGS "number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"

static int	philo_init(int argc, char **argv)
{
	int	params[6];

	if (philo_init_params(argc, argv, params) == PHILO_FAILURE)
	{
		dprintf(2, "\nUsage\n  %s %s\n", argv[0], PHILO_ARGS);
		return (PHILO_FAILURE);
	}
	return (PHILO_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (philo_init(argc, argv) == PHILO_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
