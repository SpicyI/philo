/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:03:21 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/17 17:00:30 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	philo_eat(t_philo *v)
{
	pthread_mutex_lock(&(v->fork[(v->philo - 1) % v->d->n_philos]));
	gettimeofday(&(v->ping), NULL);
	printf("%d %d has taken a fork\n", timer(v->d->t0, v->ping),
		v->philo);
	pthread_mutex_lock(&(v->fork[v->philo % v->d->n_philos]));
	gettimeofday(&(v->ping), NULL);
	printf("%d %d has taken a fork\n", timer(v->d->t0, v->ping),
		v->philo);
	gettimeofday(&(v->end), 0);
	if (timer(v->start, v->end) > (v->d->tt_die))
	{
		gettimeofday(&(v->ping), NULL);
		printf("%d %d died\n", timer(v->d->t0, v->ping), v->philo);
		return (0);
	}
	gettimeofday(&(v->start), 0);
	gettimeofday(&(v->ping), NULL);
	if (v->d->nmax_eat > 0)
		v->n_eat += 1;
	printf("%d %d is eating\n", timer(v->d->t0, v->ping), v->philo);
	ft_sleep(v->d->tt_eat * 1000);
	pthread_mutex_unlock(&(v->fork[v->philo % v->d->n_philos]));
	pthread_mutex_unlock(&(v->fork[(v->philo - 1) % v->d->n_philos]));
	return (1);
}

int	philo_sleep(t_philo *v)
{
	gettimeofday(&(v->ping), NULL);
	printf("%d %d is sleeping\n", timer(v->d->t0, v->ping), v->philo);
	ft_sleep(v->d->tt_sleep * 1000);
	return (1);
}

int	us_timer(struct timeval start, struct timeval end)
{
	int	total;

	total = ((end.tv_sec - start.tv_sec) * 1e6) + ((end.tv_usec
				- start.tv_usec));
	return (total);
}

void ft_sleep(int time_to_sleep)
{
	struct timeval	p0;
	struct timeval	p1;

	gettimeofday(&p0, 0);
	usleep(time_to_sleep / 2);
	while (1)
	{
		gettimeofday(&p1,0);
		if (us_timer(p0, p1) >= time_to_sleep)
			break;
	}
	
}
