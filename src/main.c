/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:20:35 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/01 23:32:10 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

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

int set_args(t_data *v, int ac, char **av)
{
    v->nmax_eat = -1;
    
    v->n_philos = ft_atoi(av[1]);
    if (v->n_philos <= 0)
        return (0);
    v->tt_die = ft_atoi(av[2]);
    if (v->tt_die < 0)
        return (0);
    v->tt_eat = ft_atoi(av[3]);
    if (v->tt_eat < 0)
        return (0);
    v->tt_sleep = ft_atoi(av[4]);
    if (v->tt_sleep < 0)
        return (0);
    if(ac == 6)
        v->nmax_eat = ft_atoi(av[5]);
    if (v->nmax_eat <= 0 && ac == 6)
        return(0);
    return (1);
    
}

int table_innit(t_data *v, t_philo **v1, pthread_mutex_t **lock)
{
    int i;
    int *forks;

    i = 0;
    
    forks = (int *) malloc(sizeof(int) * v->n_philos);
    if (!forks)
        return (0);
    *v1 = (t_philo *)malloc(sizeof(t_philo) * v->n_philos);
    if(!*v1)
        return (0);
    *lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * v->n_philos);
    if(!*lock)
        return (0);
    v->th = (pthread_t *)malloc(sizeof(pthread_t) * v->n_philos);
    if (!v->th)
        return (0);
    while(i < v->n_philos)
    {
        (*v1)[i].lockl = *lock;
        (*v1)[i].n_philos = v->n_philos;
        (*v1)[i].tt_die = v->tt_die;
        (*v1)[i].tt_sleep = v->tt_sleep;
        (*v1)[i].tt_eat = v->tt_eat;
        (*v1)[i].nmax_eat = v->nmax_eat;
        (*v1)[i].philo = i + 1;
        (*v1)[i].fork = forks;
        forks[i] = i + 1;
        i++;
    }
    return (1);
}

int16_t timer(struct timeval *start, struct timeval *end)
{
    int total;
    
    total =((end->tv_sec - start->tv_sec) * 1000) + ((end->tv_usec - start->tv_usec) / 1000);
    return(total);
}

void *cycle(void *p)
{
    t_philo *v;

    v = (t_philo *)p;
    int i = 0;
    gettimeofday(&(v->start), 0);
    while(1)
    {

            pthread_mutex_lock(&(v->lockl[v->philo]));
            printf("%d has taken thier fork\n",v->philo);
            pthread_mutex_lock(&(v->lockl[(v->philo + 1) % v->n_philos]));
            printf("%d has taken thier right's fork\n",v->philo);
            gettimeofday(&(v->end), 0);
            v->visa = timer(&(v->start), &(v->end));
            if(v->visa > v->tt_die)
            {
                printf("%d died cs visa %d > %d\n",v->philo,v->visa,v->tt_die);
                // return(v);
            }
            gettimeofday(&(v->start), 0);
            printf("%d has is eating \n",v->philo);
            usleep(v->tt_eat * 1000);
            pthread_mutex_unlock(&(v->lockl[(v->philo + 1) % v->n_philos]));
            pthread_mutex_unlock(&(v->lockl[v->philo]));
            printf("%d is sleeping \n",v->philo);
            usleep(v->tt_sleep * 1000);
            printf("%d is thinking \n",v->philo);
            i++;
    }
    return(p);
}

int philo(t_data *v)
{
    int i;
    t_philo *v1;
    pthread_mutex_t *lock;
    
    i = 0;
    v1 = 0;
    lock = 0;
    if (!table_innit(v, &v1 ,&lock))
        return (0);
    while(i < v->n_philos)
    {
        pthread_mutex_init(&lock[i], NULL);
        i++;
    }
                    i = 0;
                    while(i < v->n_philos)
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
                    i = 0;
    while (i < v->n_philos)
    {
        pthread_mutex_destroy(&lock[i]);
        i++;
    }
    return(1);
}

int main(int ac, char *av[])
{
    t_data v;
    
    if (ac > 6 || ac < 5)
        return (1);
    if (!set_args(&v, ac, av))
        return (2);
    if (!philo(&v))
        return (3);
    return (0);
}
