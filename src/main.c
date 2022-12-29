/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:20:35 by del-khay          #+#    #+#             */
/*   Updated: 2022/12/29 20:51:15 by del-khay         ###   ########.fr       */
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
void *cycle(void *p)
{
    t_philo *v;
    struct timeval start;
    struct timeval end;

    v = (t_philo *)p;
    gettimeofday(&start, 0);
    while((v->nmax_eat)--)
    {
        // if(v->philo % 2 == 0)
        // {
            
            pthread_mutex_lock(&(v->lockl[v->philo - 1]));
            printf("%d has taken thier fork\n",v->philo);
            if (v->philo == v->n_philos)
                pthread_mutex_lock(&(v->lockl[0]));
            else
                pthread_mutex_lock(&(v->lockl[v->philo]));
            printf("%d has taken thier right's fork\n",v->philo);
            printf("%d has is eating \n",v->philo);
            usleep(v->tt_eat);
            if (v->philo == v->n_philos)
                pthread_mutex_unlock(&(v->lockl[0]));
            else
                pthread_mutex_unlock(&(v->lockl[v->philo]));
            pthread_mutex_unlock(&(v->lockl[v->philo - 1]));
            printf("%d has is sleeping \n",v->philo);
            usleep(v->tt_sleep);
            printf("%d has is thinking \n",v->philo);
        // }
        // else if (v->philo % 2 != 0)
        // {
        //     pthread_mutex_lock(&(v->lockl[v->philo - 1]));
        //     printf("%d has taken thier fork\n",v->philo);
        //     if (v->philo == v->n_philos)
        //         pthread_mutex_lock(&(v->lockl[0]));
        //     else
        //         pthread_mutex_lock(&(v->lockl[v->philo]));
        //     printf("%d has taken thier right's fork\n",v->philo);
        //     printf("%d has is eating \n",v->philo);
        //     usleep(v->tt_eat);
        //     if (v->philo == v->n_philos)
        //         pthread_mutex_unlock(&(v->lockl[0]));
        //     else
        //         pthread_mutex_unlock(&(v->lockl[v->philo]));
        //     pthread_mutex_unlock(&(v->lockl[v->philo - 1]));
        //     printf("%d has is sleeping \n",v->philo);
        //     usleep(v->tt_sleep);
        //     printf("%d has is thinking \n",v->philo);
        //     usleep(v->tt_die - (v->tt_eat + v->tt_sleep));
        // }
        printf("**************************************\n");
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
    if (!table_innit(v, &v1 ,&lock))
        return (0);
    while(i < v->n_philos)
    {
        pthread_mutex_init(&lock[i], NULL);
        pthread_create(v->th + i, NULL, &cycle, &v1[i]);
        i++;
    }
    i = 0;
    while (i < v->n_philos)
    {
        pthread_join(*(v->th + i), NULL);
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
