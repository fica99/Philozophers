/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:41:58 by aashara-          #+#    #+#             */
/*   Updated: 2021/07/18 23:43:57 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** --Macroses--
*/
/*
** -------Limits of params-------------
*/
# define PHILO_MIN_NB_PHILO 2
# define PHILO_MIN_TIME_TO_DIE 1
# define PHILO_MIN_TIME_TO_EAT 1
# define PHILO_MIN_TIME_TO_SLEEP 1
# define PHILO_MIN_NB_EATINGS 0
/*
** --Enums--
*/
/*
** -------Philozophers actions----------
*/
typedef enum
{
	PHILO_TAKE_FORK,
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKING,
	PHILO_DIED
}	t_philo_actions;
/*
** --Structures--
*/
typedef struct				s_philo
{
	int						number;
	int						left_fork;
	int						right_fork;
	unsigned long			last_eat_time;
	int						number_of_eatings;
	struct s_philo_data		*data;
}							t_philo;

typedef struct		s_philo_data
{
	int				params[6];
	t_philo			*philozophers;
	pthread_mutex_t	*forks;
	unsigned long	start_time;
	t_philo_bool	is_running;
}					t_philo_data;

/*
** --Functions--
*/
/*
** ------------philo_utils.c------------------
*/
t_philo_bool	philo_isspace(int c);
t_philo_bool	philo_isdigit(int c);
int				philo_atoi(const char *str);
unsigned long	philo_get_current_time(void);
void			philo_print_action(t_philo_actions action, t_philo *philo);
/*
** ------------philo_init_params.c------------
*/
int				philo_init_params(int argc, char **argv, int params[6]);
int				philo_validate_params(int params[6]);
/*
** ------------philo_run.c---------------------
*/
void			*philo_run(void *philo);
void			philo_main_thread(t_philo_data *data);
#endif
