/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:19:55 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/08 18:52:07 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*INCLUDES*/
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/*ERROR MESSAGES*/
# define ARG_NUM_ERROR "The arguments sent \n"
# define FORK_CREATION_ERROR "The forks could not be created properly\n"
# define FORK_INIT_ERROR "Error while initializing the forks\n"

/*LOGS*/
# define FORK "has taken a fork\n"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

/*STRUCTS*/
typedef struct data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	long int		beginning;
	long int		now;
	pthread_mutex_t	*fork;
}			t_data;

typedef struct philo
{
	t_data			*data;
	int				id;
	pthread_t		th;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}			t_philo;

void		*life_of_a_philo(void *i);
long int	get_time(void);

/*exit_management*/
void		exit_error(char *error);

/*init*/
void		init_philos(t_philo *philo, t_data *data);
void		init_forks(t_data *data);
void		init_data(int argc, char **argv, t_data *data);

/*utils.c*/
size_t		ft_strlen(const char *str);
long		ft_atoi(const char *str);

#endif