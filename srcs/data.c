/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:48:33 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/07 17:48:12 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Checks if the number of args is good and if they are all digits. If anything
goes wrong, prints an error message before returning 1.*/
int	check_args(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
		return (error_message(ARG_NUM_ERROR), 1);
	if (ft_isdigit(argc, argv) != 0)
		return (error_message(NUMERIC_ERROR), 1);
	return (0);
}

/*Initializes all the data with the arguments that were sent to the program.
Also checks if there is not more than 200 philos, or if there is any at all.
If anything goes wrong, prints an error message before returning 1.*/
int	init_data(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	if (data->num_philos > 200)
		return (free(data), error_message(PHILO_NUM_ERROR), 1);
	if (data->num_philos < 1)
		return (free(data), error_message(ZERO_PHILO_ERROR), 1);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		return (free(data), error_message(NOT_ENOUGH_TIME_ERROR), 1);
	data->num_meals = 0;
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	data->status = 0;
	data->full_philos = 0;
	data->beginning = get_time();
	return (0);
}

/*Mallocs the fork mutex and initializes as many forks as there is philos.
If anything goes wrong, all of the previously created forks (if there were
any) are destroyed and the data is freed before printing an error message
and returning 1.*/
int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	while (data->num_philos > i)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) == -1)
		{
			if (i > 0)
			{
				while (i-- >= 0)
					pthread_mutex_destroy(&data->fork[i]);
				return (free(data->fork),
					error_message(FORK_CREATION_ERROR), 1);
			}
		}
		i++;
	}
	return (0);
}

/*Initializes all the forks one by one and then mallocs and initializes
all the necessary mutexes for the program. If anything goes wrong, prints
an error message and free all mallocked data and mutexes before returning 1.*/
int	init_mutex(t_data *data)
{
	if (init_forks(data) != 0)
		return (1);
	data->write_access = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->write_access, NULL) == -1)
		return (destroy_and_free_data(data),
			error_message(WRITE_MUTEX_ERROR), 1);
	data->status_check = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->status_check, NULL) == -1)
		return (destroy_and_free_data(data),
			error_message(DEATH_MUTEX_ERROR), 1);
	data->meals = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->meals, NULL) == -1)
		return (destroy_and_free_data(data),
			error_message(DEATH_MUTEX_ERROR), 1);
	data->time = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->time, NULL) == -1)
		return (destroy_and_free_data(data),
			error_message(DEATH_MUTEX_ERROR), 1);
	return (0);
}
