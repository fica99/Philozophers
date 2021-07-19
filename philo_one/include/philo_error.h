/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 09:15:25 by marvin            #+#    #+#             */
/*   Updated: 2021/07/19 09:15:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ERROR_H
# define PHILO_ERROR_H

/*
** --System headers--
*/
#ifdef PHILO_ENABLE_ASSERTS
/*
** ------------assert----------------------
*/
# include <assert.h>
/*
** --Common macroses--
*/
/*
** ------------Assert macroses-----
*/
# define PHILO_ASSERT(x) assert(x)
#else
# define PHILO_ASSERT(x) ((void)0)
#endif

/*
** ------------Error macroses------
*/
#ifdef PHILO_ENABLE_ERRORS
# define PHILO_ERROR(format, ...) fprintf(stderr, format __VA_OPT__(,) __VA_ARGS__)
# define PHILO_ERROR_RETURN(return_status, format, ...) { \
	PHILO_ERROR(format, __VA_ARGS__);                   \
	return return_status;                                 \
}
#else
# define PHILO_ERROR(format, ...) ((void)0)
# define PHILO_ERROR_RETURN(return_status, format, ...) return return_status
#endif

#endif
