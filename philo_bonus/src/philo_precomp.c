/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_precomp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 21:14:44 by aashara-          #+#    #+#             */
/*   Updated: 2021/10/10 17:48:03 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_precomp.h"

int	ft_min(int x, int y)
{
	if (x > y)
		return (y);
	return (x);
}

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}
