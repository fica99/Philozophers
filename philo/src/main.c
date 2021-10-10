/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:49:22 by aashara-          #+#    #+#             */
/*   Updated: 2021/10/10 16:26:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"
#include "philo.h"

t_philo_bool	philo_is_running(t_philo_data *data)
{
	t_philo_bool	is_running;

	philo_mutex_lock(&data->mutex_is_running);
	is_running = data->is_running;
	philo_mutex_unlock(&data->mutex_is_running);
	return (is_running);
}

void	philo_set_is_running(t_philo_data *data, t_philo_bool is_running)
{
	philo_mutex_lock(&data->mutex_is_running);
	data->is_running = is_running;
	philo_mutex_unlock(&data->mutex_is_running);
}

void	philo_free_data(t_philo_data *data)
{
	int	i;

	if (philo_mutex_destroy(&data->mutex_writing) != PHILO_SUCCESS
		|| philo_mutex_destroy(&data->mutex_is_running) != PHILO_SUCCESS)
		return ;
	i = -1;
	while (++i < data->params[0])
	{
		if (philo_mutex_destroy(data->forks + i) != PHILO_SUCCESS
			|| philo_mutex_destroy(&data->philozophers[i].mutex_eating)
			!= PHILO_SUCCESS)
			return ;
	}
	if (data->philozophers != NULL)
		free(data->philozophers);
	if (data->forks != NULL)
		free(data->forks);
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
