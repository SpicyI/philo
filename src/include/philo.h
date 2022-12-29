/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:20:46 by del-khay          #+#    #+#             */
/*   Updated: 2022/12/29 20:31:44 by del-khay         ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_mutex_t *lockl;
	int	n_philos;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	nmax_eat;
	int philo;
	int *fork;
}	t_philo;

typedef struct s_dat
{
	int	n_philos;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	nmax_eat;
	pthread_t	*th;
}		t_data;

/*-------------parcing-----------*/
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
int		alldigit(char *s);
int		set_args(t_data *v, int ac, char **av);
#endif
