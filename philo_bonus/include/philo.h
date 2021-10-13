/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:41:58 by aashara-          #+#    #+#             */
/*   Updated: 2021/10/13 11:26:12 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** --Macroses--
*/
/*
** -------Limits--------------------
*/
# define PHILO_SEM_MAX_LENGTH_NAME 260
/*
** -------Params names--------------------
*/
# define PHILO_NB_PHILO "number_of_philosophers"
# define PHILO_TIME_TO_DIE "time_to_die"
# define PHILO_TIME_TO_EAT "time_to_eat"
# define PHILO_TIME_TO_SLEEP "time_to_sleep"
# define PHILO_NB_EATINGS "number_of_times_each_philosopher_must_eat"
/*
** -------Limits of params-------------
*/
# define PHILO_MAX_NB_ARGS 6
# define PHILO_MIN_NB_PHILO 0
# define PHILO_MIN_TIME_TO_DIE 0
# define PHILO_MIN_TIME_TO_EAT 0
# define PHILO_MIN_TIME_TO_SLEEP 0
# define PHILO_MIN_NB_EATINGS 0
/*
** -------Philozophers actions text-----
*/
# define PHILO_TAKE_FORK_TEXT "has taken a fork"
# define PHILO_EATING_TEXT "is eating"
# define PHILO_SLEEPING_TEXT "is sleeping"
# define PHILO_THINKING_TEXT "is thinking"
# define PHILO_DIED_TEXT "died"
/*
** -------Semaphore names-----
*/
# define PHILO_SEM_FORKS "/philo_semaphore_forks"
# define PHILO_SEM_WRITING "/philo_semaphore_writing"
# define PHILO_SEM_EATING "/philo_semaphore_eating"
/*
** --Enums--
*/
/*
** -------Philozophers actions----------
*/
typedef enum e_philo_actions
{
	PHILO_TAKE_FORK,
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKING,
	PHILO_DIED
}				t_philo_actions;
/*
** --Structures--
*/
typedef struct s_philo
{
	pid_t				pid;
	int					id;
	unsigned long		last_eat_time;
	int					nb_eat;
	struct s_philo_data	*data;
	sem_t				*sem_eating;
}						t_philo;

typedef struct s_philo_data
{
	int				par[PHILO_MAX_NB_ARGS];
	t_philo			*philozophers;
	sem_t			*sem_forks;
	sem_t			*sem_writing;
}					t_philo_data;

/*
** --Functions--
*/
/*
** ------------philo_time.c-----------------
*/
unsigned long	philo_elapsed_time(void);
int				philo_smart_sleep(unsigned long sleep_time_ms);
/*
** ------------philo_utils.c------------------
*/
t_philo_bool	philo_is_int(const char *str);
int				philo_atoi(const char *str);
void			philo_print_action(t_philo_actions action, t_philo *philo);
/*
** ------------philo_init.c------------
*/
int				philo_init(int argc, char **argv, t_philo_data *data);
/*
** ------------philo_run.c---------------------
*/
int				philo_run_processes(t_philo_data *data);
/*
** ------------main.c--------------------------
*/
void			philo_free_data(t_philo_data *data);
/*
** ------------philo_sem.c--------------------------
*/
char			*philo_sem_name(char const *base, char *buffer, int position);
int				philo_sem_close(sem_t **sem, const char *name);
int				philo_sem_open(sem_t **sem, const char *name,
					unsigned int value);
int				philo_sem_wait(sem_t *sem);
int				philo_sem_post(sem_t *sem);
#endif
