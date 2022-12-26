/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:39:10 by del-khay          #+#    #+#             */
/*   Updated: 2022/12/25 20:43:28 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"


static	int	checkmaxmin(long n)
{
	if (n < INT_MIN || n > INT_MAX)
	{
		return (-1);
	}
	return (n);
}

int	ft_atoi(const char *nptr)
{
	int					s;
	unsigned long long	rslt;

	s = 1;
	rslt = 0;
	if (!alldigit((char *)nptr))
		return (-1);
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			s *= -1;
		nptr++;
	}
	while (*nptr > 47 && *nptr < 58)
	{
		rslt = rslt * 10 + (*nptr - '0');
		nptr++;
	}
	return(checkmaxmin(s * rslt));
}
