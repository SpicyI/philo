/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:20:46 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/23 23:11:36 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
/*------------includes--------------*/
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
/*------------defines---------------*/
# define FORKS "forks_sem"
# define ALLPID 0
/*------------structs---------------*/
struct	s_data;

typedef struct s_philo
{
	struct s_data	*d;
	int				philo;
	int				n_eat;
	struct timeval	start;
	struct timeval	ping;
}					t_philo;

typedef struct s_data
{
	int				n_philos;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				nmax_eat;
	sem_t			*forks;
	pid_t			*pid;
	struct timeval	t0;
	struct timeval	end;
}					t_data;

/*-------------parcing-----------*/
int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *s);
int					alldigit(char *s);
int					set_args(t_data *v, int ac, char **av);
/*-------------innit-----------*/
int					table_init(t_data *v, t_philo **v1);
/*-------------cycle-----------*/
void				*cycle(void *p);
int					philo_eat(t_philo *v);
int					timer(struct timeval start, struct timeval end);
int					philo_sleep(t_philo *v);
void				ft_sleep(int time_to_sleep);
int					us_timer(struct timeval start, struct timeval end);
void				philo_process(t_philo *v);
void				ft_exit(t_data *v);
void				check_death(t_philo *v1, t_data *v);

#endif
