/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:20:35 by del-khay          #+#    #+#             */
/*   Updated: 2023/05/29 17:09:51 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	timer(struct timeval start, struct timeval end)
{
	int	total;

	total = ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_usec
				- start.tv_usec) / 1000);
	return (total);
}

void	*cycle(void *p)
{
	t_philo	*v;

	v = (t_philo *)p;
	gettimeofday(&(v->start), 0);
	if ((v->philo % 2))
		usleep(1500);
	while (v->d->death)
	{
		if (exit_condition(v))
			return (0);
		philo_eat(v);
		if (v->d->nmax_eat > 0)
			v->n_eat++;
		if (v->d->nmax_eat > 0 && v->n_eat == v->d->nmax_eat)
		{
			pthread_mutex_lock(&v->d->neat_lock);
			v->d->philos_in_table--;
			pthread_mutex_unlock(&v->d->neat_lock);
			return (0);
		}
		philo_sleep(v);
		usleep(50);
	}
	return (0);
}

void	check_death(t_philo *v1, t_data *v)
{
	int				i;
	struct timeval	ping;

	while (v->death)
	{
		i = -1;
		while (++i < v->n_philos)
		{
			gettimeofday(&v->end, 0);
			pthread_mutex_lock(&v->death_lock);
			pthread_mutex_lock(&v->neat_lock);
			if (v->philos_in_table == 0)
				return ;
			pthread_mutex_unlock(&v->neat_lock);
			if (timer(v1[i].start, v->end) > v->tt_die)
			{
				v->death = 0;
				gettimeofday(&ping, NULL);
				printf("%5d %d died\n", timer(v->t0, ping), v1[i].philo);
				return ;
			}
			pthread_mutex_unlock(&v->death_lock);
			if (v->death == 0)
				return ;
			usleep(30);
		}
	}
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
	check_death(v1, v);
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
