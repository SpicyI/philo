/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:20:35 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/24 16:47:46 by del-khay         ###   ########.fr       */
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
		usleep(1000);
	while (1)
	{
		philo_eat(v);
		if (v->d->nmax_eat > 0)
		{
			v->n_eat++;
			if (v->n_eat == v->d->nmax_eat)
				exit(v->d->n_philos + 2);
		}
		philo_sleep(v);
		gettimeofday(&(v->ping), NULL);
		usleep(50);
	}
	return (0);
}

void	check_death(t_philo *v1, t_data *v)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < v->n_philos)
		{
			gettimeofday(&v->end, 0);
			if (timer(v1->start, v->end) > v->tt_die)
				exit(v1->philo);
			i++;
			usleep(30);
		}
	}
}

int	philo(t_data *v)
{
	int		i;
	t_philo	*v1;

	i = 0;
	v1 = 0;
	if (!table_init(v, &v1))
		return (0);
	gettimeofday(&(v->t0), NULL);
	while (i < v->n_philos)
	{
		v->pid[i] = fork();
		if (v->pid[i] == 0)
		{
			philo_process(&v1[i]);
			exit(0);
		}
		i++;
	}
	ft_exit(v);
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
