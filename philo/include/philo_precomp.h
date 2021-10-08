/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_precomp.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 21:13:15 by aashara-          #+#    #+#             */
/*   Updated: 2021/07/22 22:14:31 by aashara-         ###   ########.fr       */
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
#include <limits.h>
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
** ------------pthread_mutex_init---------
** ------------pthread_create-------------
** ------------pthread_join---------------
** ------------pthread_mutex_lock---------
*/
# include <pthread.h>
/*
** ------------gettimeofday----------------
*/
# include <sys/time.h>
/*
** ------------usleep----------------------
*/
# include <unistd.h>
/*
** --Macroses--
*/
/*
** ------------Return status macroses-----
*/
# define PHILO_SUCCESS 0
# define PHILO_FAILURE -1
/*
** ------------MAX/MIN--------------------
*/
#define FT_MIN(x, y) (((x) > (y)) ? (y) : (x))
#define FT_MAX(x, y) (((x) > (y)) ? (x) : (y))
/*
** --Enums--
*/
/*
** ------------Boolean values-------------
*/
typedef	enum
{
	Philo_false = 0,
	Philo_true = 1
}				t_philo_bool;
#endif
