/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:34:34 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/11 20:40:55 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	table_init(t_data *v, t_philo **v1, pthread_mutex_t **lock)
{
	int	i;

	i = 0;
	*v1 = (t_philo *)malloc(sizeof(t_philo) * v->n_philos);
	if (!*v1)
		return (0);
	*lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * v->n_philos);
	if (!*lock)
		return (0);
	v->th = (pthread_t *)malloc(sizeof(pthread_t) * v->n_philos);
	if (!v->th)
		return (0);
	memset(*lock, 0, v->n_philos * sizeof(pthread_mutex_t));
	memset(v->th, 0, v->n_philos * sizeof(pthread_t));
	while (i < v->n_philos)
	{
		(*v1)[i].fork = *lock;
		(*v1)[i].d = v;
		(*v1)[i].n_eat = 0;
		(*v1)[i].philo = i + 1;
		i++;
	}
	v->death = 1;
	v->philos_in_table = v->n_philos;
	return (1);
}

int	m_lock(pthread_mutex_t *lock, t_data *v)
{
	int	i;

	i = 0;
	while (i < v->n_philos)
	{
		if(pthread_mutex_init(&lock[i], NULL) == -1)
			return (0);
		i++;
	}
	return (1);
}

int	m_unlock(pthread_mutex_t *lock, t_data *v)
{
	int	i;

	i = 0;
	while (i < v->n_philos)
	{
		if(pthread_mutex_destroy(&lock[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}
