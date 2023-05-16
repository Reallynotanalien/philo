/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:36:21 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/16 15:00:24 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
				free(data->fork);
				error_message(FORK_CREATION_ERROR);
				return (1);
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
	{
		destroy_forks(data);
		free(data->fork);
		free(data->write_access);
		error_message(WRITE_MUTEX_ERROR);
		return (1);
	}
	data->death = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->death, NULL) == -1)
	{
		destroy_forks(data);
		pthread_mutex_destroy(data->write_access);
		free(data->fork);
		free(data->write_access);
		free(data->death);
		error_message(DEATH_MUTEX_ERROR);
		return (1);
	}
	data->full = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->full, NULL) == -1)
	{
		destroy_forks(data);
		pthread_mutex_destroy(data->write_access);
		pthread_mutex_destroy(data->death);
		free(data->fork);
		free(data->write_access);
		free(data->death);
		error_message(FULL_MUTEX_ERROR);
		return (1);
	}
	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	if (data->num_philos > 200)
	{
		error_message(PHILO_NUM_ERROR);
		return (1);
	}
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_die < 60|| data->time_to_eat < 60
		|| data->time_to_sleep < 60)
	{
		error_message(NOT_ENOUGH_TIME_ERROR);
		return (1);
	}
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	data->beginning = get_time();
	return (0);
}
