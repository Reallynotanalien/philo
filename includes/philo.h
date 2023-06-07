/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:19:55 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/07 17:48:19 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*INCLUDES*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/*INT VARIABLES*/
# define FULL 1
# define DEAD 2
# define TIME_TO_DIE 3
# define TIME_TO_EAT 4
# define TIME_TO_SLEEP 5

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
# define DIE "died 💀\n"
# define STOP_EATING "Everyone is full! 🤰\n"

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
	pthread_mutex_t	*fork;
	pthread_mutex_t	*write_access;
	pthread_mutex_t	*status_check;
	pthread_mutex_t	*meals;
	pthread_mutex_t	*time;
}			t_data;

typedef struct philo
{
	t_data			*data;
	int				id;
	int				status;
	int				meals;
	long int		timer;
	pthread_t		th;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}			t_philo;

/*data*/
int			check_args(int argc, char **argv);
int			init_data(int argc, char **argv, t_data *data);
int			init_mutex(t_data *data);

/*death*/
void		change_status_to_dead(t_philo *philo);
int			check_if_someone_died(t_philo *philo);
int			check_if_dead(t_philo *philo);
void		undertaker(t_philo *philo, t_data *data);

/*free*/
void		destroy_forks(t_data *data);
void		destroy_mutexes(t_data *data);
void		free_all_data(t_data *data);
void		destroy_and_free_data(t_data *data);

/*meals*/
void		change_status_to_full(t_philo *philo);
int			check_if_everyone_is_full(t_philo *philo);
void		eating(t_philo *philo);

/*philos*/
int			init_philos(t_philo *philo, t_data *data);
void		wait_for_philos(t_philo *philo);

/*thread*/
void		print_message(char *message, t_philo *philo);
void		*life_of_a_philo(void *i);

/*time*/
long int	get_time(void);
long int	get_time_in_ms(t_philo *philo);
void		waiting(int time, t_philo *philo);
long int	check_timer(t_philo *philo);
void		adjust_timer(t_philo *philo);

/*utils*/
int			ft_isdigit(int argc, char **argv);
size_t		ft_strlen(const char *str);
long		ft_atoi(const char *str);
int			ft_strcmp(const char *str1, const char *str2);
void		error_message(char *error);

#endif