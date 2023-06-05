/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:48:33 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/05 15:18:26 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
		return (error_message(ARG_NUM_ERROR), 1);
	if (ft_isdigit(argc, argv) != 0)
		return (error_message(NUMERIC_ERROR), 1);
	return (0);
}

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

int	init_mutex(t_data *data)
{
	if (init_forks(data) != 0)
		return (1);
	data->write_access = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->write_access, NULL) == -1)
		return (destroy_and_free_data(data),
			error_message(WRITE_MUTEX_ERROR), 1);
	data->death = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->death, NULL) == -1)
		return (destroy_and_free_data(data),
			error_message(DEATH_MUTEX_ERROR), 1);
	data->full = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->full, NULL) == -1)
		return (destroy_and_free_data(data),
			error_message(DEATH_MUTEX_ERROR), 1);
	data->time = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->time, NULL) == -1)
		return (destroy_and_free_data(data),
			error_message(DEATH_MUTEX_ERROR), 1);
	return (0);
}
