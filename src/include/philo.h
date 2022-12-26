/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:20:46 by del-khay          #+#    #+#             */
/*   Updated: 2022/12/26 18:53:41 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
/*------------includes--------------*/
# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef	struct s_table
{
		int *philos;
		int *forks;
}		t_table;
typedef struct s_philo
{
	int	n_philos;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	nmax_eat;
}		t_philo;

/*-------------parcing-----------*/
int	ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
int	alldigit(char *s);
int set_args(t_philo *v, int ac, char **av);
#endif
