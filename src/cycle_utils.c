/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:03:21 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/11 01:52:35 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	philo_eat(t_philo *v)
{
	pthread_mutex_lock(&(v->lockl[(v->philo - 1) % v->d->n_philos]));
	gettimeofday(&(v->ping), NULL);
	printf("%d: %d has taken right fork\n", timer(&(v->d->t0), &(v->ping)),
		v->philo);
	pthread_mutex_lock(&(v->lockl[v->philo % v->d->n_philos]));
	gettimeofday(&(v->ping), NULL);
	printf("%d: %d has taken left fork\n", timer(&(v->d->t0), &(v->ping)),
		v->philo);
	gettimeofday(&(v->end), 0);
	if (timer(&(v->start), &(v->end)) > (v->d->tt_die))
	{
		gettimeofday(&(v->ping), NULL);
		printf("%d: %d is dead \n", timer(&(v->d->t0), &(v->ping)), v->philo);
		return (0);
	}
	gettimeofday(&(v->start), 0);
	gettimeofday(&(v->ping), NULL);
	if (v->d->nmax_eat > 0)
		v->n_eat += 1;
	printf("%d: %d has is eating \n", timer(&(v->d->t0), &(v->ping)), v->philo);
	usleep(v->d->tt_eat * 1000);
	pthread_mutex_unlock(&(v->lockl[v->philo % v->d->n_philos]));
	pthread_mutex_unlock(&(v->lockl[(v->philo - 1) % v->d->n_philos]));
	return (1);
}

int	philo_sleep(t_philo *v)
{
	gettimeofday(&(v->ping), NULL);
	printf("%d: %d is sleeping \n", timer(&(v->d->t0), &(v->ping)), v->philo);
	usleep(v->d->tt_sleep * 1000);
	return (1);
}
