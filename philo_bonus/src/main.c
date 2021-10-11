/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:49:22 by aashara-          #+#    #+#             */
/*   Updated: 2021/10/10 18:16:57 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo.h"

void	philo_free_data(t_philo_data *data)
{
	int	i;

	if (philo_sem_destroy(&data->sem_forks) != PHILO_SUCCESS
		|| philo_sem_destroy(&data->sem_writing) != PHILO_SUCCESS)
		return ;
	i = -1;
	while (++i < data->par[0])
	{
		if (philo_sem_destroy(data->philozophers[i].sem_eating)
			!= PHILO_SUCCESS)
			return ;
	}
	if (data->philozophers != NULL)
		free(data->philozophers);
}

int	main(int argc, char **argv)
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
