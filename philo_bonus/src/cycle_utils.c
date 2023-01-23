/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:03:21 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/23 23:26:09 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	philo_eat(t_philo *v)
{
	sem_wait(v->d->forks);
	gettimeofday(&(v->ping), NULL);
	printf("%5d %d has taken a fork\n", timer(v->d->t0, v->ping), v->philo);
	sem_wait(v->d->forks);
	gettimeofday(&v->start, NULL);
	gettimeofday(&(v->ping), NULL);
	printf("%5d %d has taken a fork\n", timer(v->d->t0, v->ping), v->philo);
	printf("%5d %d is eating\n", timer(v->d->t0, v->ping), v->philo);
	ft_sleep(v->d->tt_eat * 1000);
	sem_post(v->d->forks);
	sem_post(v->d->forks);
	return (1);
}

int	philo_sleep(t_philo *v)
{
	gettimeofday(&(v->ping), NULL);
	printf("%5d %d is sleeping\n", timer(v->d->t0, v->ping), v->philo);
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

void	ft_sleep(int time_to_sleep)
{
	struct timeval	p0;
	struct timeval	p1;

	gettimeofday(&p0, 0);
	while (1)
	{
		gettimeofday(&p1, 0);
		if (us_timer(p0, p1) >= time_to_sleep)
			break ;
		usleep(300);
	}
}
