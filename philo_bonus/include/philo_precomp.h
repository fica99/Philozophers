/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_precomp.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 21:13:15 by aashara-          #+#    #+#             */
/*   Updated: 2021/10/10 17:47:57 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PRECOMP_H
# define PHILO_PRECOMP_H

/*
** --System headers--
*/
/*
** ------------Limits macroses------------
*/
# include <limits.h>
/*
** ------------Exit macroses--------------
** ------------malloc---------------------
*/
# include <stdlib.h>
/*
** ------------printf---------------------
** ------------dprintf--------------------
*/
# include <stdio.h>
/*
** ------------memset---------------------
*/
# include <string.h>
/*
** ------------pthread_create-------------
** ------------pthread_join---------------
*/
# include <pthread.h>
/*
** ------------sem_open-------------------
** ------------sem_close------------------
** ------------sem_wait-------------------
** ------------sem_post-------------------
*/
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
/*
** ------------gettimeofday----------------
*/
# include <sys/time.h>
/*
** ------------fork------------------------
** ------------usleep----------------------
*/
# include <unistd.h>
/*
** ------------fork------------------------
** ------------waitpid---------------------
*/
# include <sys/types.h>
# include <sys/wait.h>
/*
** --Macroses--
*/
/*
** ------------Return status macroses-----
*/
# define PHILO_SUCCESS 0
# define PHILO_FAILURE -1
/*
** --Enums--
*/
/*
** ------------Boolean values-------------
*/
typedef enum e_philo_bool
{
	Philo_false = 0,
	Philo_true = 1,
}	t_philo_bool;
#endif
