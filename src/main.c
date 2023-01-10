/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:20:35 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/10 15:55:17 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	timer(struct timeval *start, struct timeval *end)
{
	int	total;

	total = ((end->tv_sec - start->tv_sec) * 1000) + ((end->tv_usec
				- start->tv_usec) / 1000);
	return (total);
}

void	*cycle(void *p)
{
	t_philo	*v;
	int		i;

	v = (t_philo *)p;
	i = 0;
	gettimeofday(&(v->start), 0);
	if (v->philo % 2)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&(v->lockl[(v->philo - 1) % v->d->n_philos]));
		printf("%d has taken thier fork\n", v->philo);
		pthread_mutex_lock(&(v->lockl[v->philo % v->d->n_philos]));
		printf("%d has taken thier right's fork\n", v->philo);
		gettimeofday(&(v->end), 0);
		v->visa = timer(&(v->start), &(v->end));
		if (v->visa > (v->d->tt_die))
		{
			printf("%d %ld > %d\n", v->philo, v->visa, v->d->tt_die);
		}
		gettimeofday(&(v->start), 0);
		printf("%d has is eating \n", v->philo);
		usleep(v->d->tt_eat * 1000);
		pthread_mutex_unlock(&(v->lockl[v->philo % v->d->n_philos]));
		pthread_mutex_unlock(&(v->lockl[(v->philo - 1) % v->d->n_philos]));
		printf("%d is sleeping \n", v->philo);
		usleep(v->d->tt_sleep * 1000);
		printf("%d is thinking \n", v->philo);
		i++;
	}
	return (p);
}

int	philo(t_data *v)
{
	int				i;
	t_philo			*v1;
	pthread_mutex_t	*lock;
    
	i = 0;
	v1 = 0;
	lock = 0;
	if (!table_init(v, &v1, &lock))
		return (0);
	if (!m_lock(lock, v))
		return (0);
    gettimeofday(&(v->t0),NULL);
	while (i < v->n_philos)
	{
		pthread_create(v->th + i, NULL, &cycle, &v1[i]);
		i++;
	}
	i = 0;
	while (i < v->n_philos)
	{
		pthread_join(*(v->th + i), NULL);
		i++;
	}
	if (!m_unlock(lock, v))
		return (0);
	return (1);
}

int	main(int ac, char *av[])
{
	t_data	v;

	if (ac > 6 || ac < 5)
		return (1);
	if (!set_args(&v, ac, av))
		return (2);
	if (!philo(&v))
		return (3);
	return (0);
}
