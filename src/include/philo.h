/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:20:46 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/10 15:52:33 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
/*------------includes--------------*/
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/*------------structs---------------*/
struct s_data;

typedef struct s_philo
{
	pthread_mutex_t	*lockl;
	struct s_data	*d;
	int				philo;
	struct timeval	start;
	struct timeval	end;
	suseconds_t		visa;
}					t_philo;

typedef struct s_data
{
	int				n_philos;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				nmax_eat;
    struct timeval  t0;
	pthread_t		*th;
}					t_data;

/*-------------parcing-----------*/
int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *s);
int					alldigit(char *s);
int					set_args(t_data *v, int ac, char **av);
/*-------------innit-----------*/
int					m_unlock(pthread_mutex_t *lock, t_data *v);
int					m_lock(pthread_mutex_t *lock, t_data *v);
int					table_init(t_data *v, t_philo **v1, pthread_mutex_t **lock);
#endif
