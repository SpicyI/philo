/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:20:35 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/11 23:34:33 by del-khay         ###   ########.fr       */
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

	v = (t_philo *)p;
	gettimeofday(&(v->start), 0);
	if (v->philo % 2)
		usleep(100);
	while (v->d->death)
	{
		v->d->death = philo_eat(v);
		if (v->n_eat == v->d->nmax_eat)
		{
			v->d->philos_in_table -= 1;
			break ;
		}
		if (v->d->death == 0)
			break ;
		philo_sleep(v);
		gettimeofday(&(v->ping), NULL);
		printf("%d %d is thinking\n", timer(&(v->d->t0), &(v->ping)),
			v->philo);
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
	gettimeofday(&(v->t0), NULL);
	while (i < v->n_philos)
	{
		pthread_create(v->th + i, NULL, &cycle, &v1[i]);
		pthread_detach(v->th[i++]);
	}
	while (v->death)
	{
		if (v->philos_in_table == 0)
			break ;
	}
	if (!m_unlock(lock, v))
		return (0);
	return (1);
}

// int	main(int ac, char *av[])
// {
// 	t_data	v;

// 	if (ac > 6 || ac < 5)
// 		return (1);
// 	if (!set_args(&v, ac, av))
// 		return (2);
// 	if (!philo(&v))
// 		return (3);
// 	return (0);
// }
