/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:48:03 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/11 21:06:44 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static int	checkmaxmin(long n)
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
	return (checkmaxmin(s * rslt));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	alldigit(char *s)
{
	if (!s || !ft_strlen(s))
		return (0);
	if (!(*s > 47 && *s < 58) && *s != '+' && *s != '-')
		return (0);
	if (ft_strlen(s) == 1 && *s == '+' && *s == '-')
		return (0);
	s++;
	while (*s)
	{
		if (!(*s > 47 && *s < 58))
			return (0);
		s++;
	}
	return (1);
}

int	set_args(t_data *v, int ac, char **av)
{
	v->nmax_eat = -1;
	v->n_philos = ft_atoi(av[1]);
	if (v->n_philos <= 0)
	{
		// if(v->n_philos == 1)
		// {
		// 	usleep(v->tt_die * 1000);
		// 	printf("")
		// }
		return (0);
	}
	v->tt_die = ft_atoi(av[2]);
	if (v->tt_die <= 0)
		return (0);
	v->tt_eat = ft_atoi(av[3]);
	if (v->tt_eat <= 0)
		return (0);
	v->tt_sleep = ft_atoi(av[4]);
	if (v->tt_sleep <= 0)
		return (0);
	if (ac == 6)
	{
		v->nmax_eat = ft_atoi(av[5]);
		if (v->nmax_eat <= 0)
			return (0);
	}
	return (1);
}
