/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:41:58 by aashara-          #+#    #+#             */
/*   Updated: 2021/07/22 23:17:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** --Macroses--
*/
/*
** -------Params names--------------------
*/
# define PHILO_NB_PHILO "Number_of_philosophers"
# define PHILO_TIME_TO_DIE "Time_to_die"
# define PHILO_TIME_TO_EAT "Time_to_eat"
# define PHILO_TIME_TO_SLEEP "Time_to_sleep"
# define PHILO_NB_EATINGS "Number_of_times_each_philosopher_must_eat"
/*
** -------Limits of params-------------
*/
# define PHILO_MAX_NB_ARGS 6
# define PHILO_MIN_NB_PHILO 2
# define PHILO_MAX_NB_PHILO 200
# define PHILO_MIN_TIME_TO_DIE 60
# define PHILO_MIN_TIME_TO_EAT 60
# define PHILO_MIN_TIME_TO_SLEEP 60
# define PHILO_MIN_NB_EATINGS 1
/*
** -------Philozophers actions text-----
*/
# define PHILO_TAKE_FORK_TEXT "has taken a fork"
# define PHILO_EATING_TEXT "is eating"
# define PHILO_SLEEPING_TEXT "is sleeping"
# define PHILO_THINKING_TEXT "is thinking"
# define PHILO_DIED_TEXT "died"
/*
** -------Mutex lock/unlock-------------
*/
# define PHILO_LOCK(mutex) {                            \
	if (pthread_mutex_lock(mutex) != 0)                 \
		PHILO_ERROR("Error in pthread_mutex_lock\n");   \
}
# define PHILO_UNLOCK(mutex) {                          \
	if (pthread_mutex_unlock(mutex) != 0)               \
		PHILO_ERROR("Error in pthread_mutex_unlock\n"); \
}
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
typedef struct			s_philo
{
	int					number;
	int					left_fork;
	int					right_fork;
	unsigned long		last_eat_time;
	int					number_of_eatings;
	struct s_philo_data	*data;
}							t_philo;

typedef struct		s_philo_data
{
	int				params[PHILO_MAX_NB_ARGS];
	t_philo			*philozophers;
	pthread_mutex_t	*forks;
	unsigned long	start_time;
	t_philo_bool	is_running;
	pthread_mutex_t	mutex_writing;
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
** ------------philo_init.c------------
*/
int				philo_init(int argc, char **argv, t_philo_data *data);
/*
** ------------philo_run.c---------------------
*/
void			*philo_run(void *philo);
void			philo_main_thread(t_philo_data *data);
/*
** ------------main.c--------------------------
*/
void			philo_free_data(t_philo_data *data);
#endif
