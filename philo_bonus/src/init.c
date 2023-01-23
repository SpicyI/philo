/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:34:34 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/23 23:28:56 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	table_init(t_data *v, t_philo **v1)
{
	int	i;

	i = 0;
	*v1 = (t_philo *)malloc(sizeof(t_philo) * v->n_philos);
	v->pid = (pid_t *)malloc(sizeof(pid_t) * v->n_philos);
	if (!*v1 || !v->pid)
		return (0);
	sem_unlink(FORKS);
	v->forks = sem_open(FORKS, O_CREAT, S_IRWXU, v->n_philos);
	while (i < v->n_philos)
	{
		(*v1)[i].d = v;
		(*v1)[i].n_eat = 0;
		(*v1)[i].philo = i + 1;
		i++;
	}
	return (1);
}

void	philo_process(t_philo *v)
{
	pthread_t	thread;

	gettimeofday(&v->start, NULL);
	pthread_create(&thread, NULL, &cycle, v);
	pthread_detach(thread);
	check_death(v, v->d);
}

void	ft_exit(t_data *v)
{
	int	i;
	int	status;

	i = 0;
	while (1)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			status = WEXITSTATUS(status);
			gettimeofday(&v->end, NULL);
			printf("%5d %d died\n", timer(v->t0, v->end), status);
			while (i < v->n_philos)
			{
				kill(v->pid[i], SIGKILL);
				i++;
			}
			sem_close(v->forks);
			sem_unlink(FORKS);
			exit(0);
		}
		usleep(30);
	}
}
