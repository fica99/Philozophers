/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:41:58 by aashara-          #+#    #+#             */
/*   Updated: 2021/06/05 23:05:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** --Structures--
*/

typedef struct		s_philo_data t_philo_data;
typedef struct		s_philo
{
	int				number;
	int				left_fork;
	int				right_fork;
	t_philo_data	*data;
}					t_philo;

struct		s_philo_data
{
	int				params[6];
	int				start_time;
	t_philo			*philozophers;
	pthread_mutex_t	*forks;
};

/*
** --Functions--
*/
/*
** ------------philo_utils.c------------------
*/
t_philo_bool	philo_isspace(int c);
t_philo_bool	philo_isdigit(int c);
int				philo_atoi(const char *str);
int				philo_get_current_time(void);
/*
** ------------philo_init_params.c------------
*/
int				philo_init_params(int argc, char **argv, int params[6]);
int				philo_validate_params(int params[6]);
/*
** ------------philo_run.c---------------------
*/
void			*philo_run(void *philo);
#endif
