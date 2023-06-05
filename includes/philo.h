/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:19:55 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/05 15:04:35 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*INCLUDES*/
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define END 1
# define DEAD 2
# define IDLE 3

/*ERROR MESSAGES*/
# define ARG_NUM_ERROR "The program needs between 5 and 6 arguments: \
number_of_philos time_to_die time_to_eat time_to_sleep [number of \
meals].\n"
# define NUMERIC_ERROR "The arguments should be numbers.\n"
# define PHILO_NUM_ERROR "There is too many philosophers! This table \
only holds 200 of them.\n"
# define ZERO_PHILO_ERROR "There should be at least one philosopher at \
this table for the simulation to take place!\n"
# define NOT_ENOUGH_TIME_ERROR "You should leave more than 60ms for each \
philo to eat, sleep or die. Come on.\n"
# define FORK_CREATION_ERROR "The forks could not be created properly. Oups!\n"
# define THREAD_CREATE_ERROR "The thread could not be created properly. Oups!\n"
# define WRITE_MUTEX_ERROR "Could not create the write_access mutex. Oups!\n"
# define DEATH_MUTEX_ERROR "Could not create the death mutex. Oups!\n"

/*LOGS*/
# define FORK "has taken a fork 🍴\n"
# define EAT "is eating 🍝\n"
# define SLEEP "is sleeping 💤\n"
# define THINK "is thinking 💭\n"
# define DIE "died ☠️\n"

/*STRUCTS*/
typedef struct data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				status;
	int				full_philos;
	long int		beginning;
	long int		now;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*write_access;
	pthread_mutex_t	*death;
	pthread_mutex_t	*full;
	pthread_mutex_t	*time;
}			t_data;

typedef struct philo
{
	t_data			*data;
	int				id;
	int				status;
	int				meals;
	int				num_philos;
	long int		timer;
	long int		death_time;
	pthread_t		th;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}			t_philo;

void		*life_of_a_philo(void *i);
void		free_all(t_data *data);
void		print_message(char *message, t_philo *philo);
long int	get_time(void);
int			check_if_someone_died(t_philo *philo);
int			check_if_dead(t_philo *philo);

/*data*/
int			check_args(int argc, char **argv);

/*death*/
void		change_status(t_philo *philo);
void		undertaker(t_philo *philo, t_data *data);

/*error*/
void		error_message(char *error);
// void		free_all(t_philo *philo, t_data *data);
// void		destroy_forks(t_data *data);
// void		destroy_all_mutex(t_data *data);

/*free*/
void		destroy_forks(t_data *data);
void		destroy_mutexes(t_data *data);
void		destroy_and_free_data(t_data *data);

/*init*/
int			init_philos(t_philo *philo, t_data *data);
int			init_mutex(t_data *data);
int			init_data(int argc, char **argv, t_data *data);

/*time*/
void		waiting(long int ms);

/*utils*/
int			ft_isdigit(int argc, char **argv);
size_t		ft_strlen(const char *str);
long		ft_atoi(const char *str);
int			ft_strcmp(const char *str1, const char *str2);

#endif