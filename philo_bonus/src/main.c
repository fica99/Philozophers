/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:49:22 by aashara-          #+#    #+#             */
/*   Updated: 2021/08/09 20:57:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo_error.h"
#include "philo.h"

void		philo_free_data(t_philo_data *data)
{
	if ((sem_close(PHILO_SEMAPHORE_WRITE) != 0)
		PHILO_ERROR_RETURN(PHILO_FAILURE, "Cannot close writing semaphore\n");
	if (data->philozophers != NULL)
		free(data->philozophers);
	if (data->forks != NULL)
		free(data->forks);
}

int			main(int argc, char **argv)
{
	t_philo_data	data;
	int				res;

	if (philo_init(argc, argv, &data) == PHILO_FAILURE)
		return (EXIT_FAILURE);
	res = philo_run_threads(&data);
	philo_free_data(&data);
	if (res == PHILO_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
