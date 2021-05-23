/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:41:58 by aashara-          #+#    #+#             */
/*   Updated: 2021/05/23 21:50:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
/*
** --System headers--
*/
/*
** ------------Limits macroses------------
*/
#include <limits.h>
/*
** ------------Exit macroses------------
*/
# include <stdlib.h>
/*
** ------------printf------------
** ------------dprintf------------
*/
# include <stdio.h>
/*
** ------------memset------------
*/
# include <string.h>
/*
** --Common macroses--
*/
/*
** ------------Return status macroses------------
*/
# define PHILO_SUCCESS 0
# define PHILO_FAILURE -1
/*
** --Enums
*/
/*
** ------------Boolean values------------
*/
typedef	enum
{
	Philo_false = 0,
	Philo_true = 1
}				t_philo_bool;
/*
** --Structures--
*/

/*
** --Functions--
*/
/*
** ------------philo_utils.c------------
*/
t_philo_bool	philo_isspace(int c);
t_philo_bool	philo_isdigit(int c);
int						philo_atoi(const char *str);
/*
** ------------philo_init_params.c------------
*/
int						philo_init_params(int argc, char **argv, int params[6]);
#endif
