/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:36:21 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/07 21:34:48 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Initializes all the philo data and associates each philosopher with his 
respective right fork.*/
void	init_philo_data(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (data->num_philos > i)
	{
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].status = 0;
		philo[i].meals = 1;
		philo[i].timer = 0;
		philo[i].die = data->time_to_die;
		philo[i].eat = data->time_to_eat;
		philo[i].sleep = data->time_to_sleep;
		philo[i].num = data->num_philos;
		philo[i].total_meals = data->num_meals;
		philo[i].right_fork = &data->fork[i];
		i++;
	}
}

/*Initializes all of the philo data (including associating each philosopher with
his respective right fork), then creates a chain to associate the left fork of
each philo to his neighboor's right fork. One by one, the threads are created
and the routine starts. If anything goes wrong, prints and error message and
frees all mallocked data and destroy all mutexes before returning 1. */
int	init_philos(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	init_philo_data(philo, data);
	while (data->num_philos > i)
	{
		if (i == 0)
			philo[i].left_fork = philo[data->num_philos - 1].right_fork;
		else
			philo[i].left_fork = philo[i - 1].right_fork;
		if (pthread_create(&philo[i].th, NULL, &life_of_a_philo,
				&philo[i]) != 0)
			return (destroyer(data), free(philo),
				error_message(THREAD_CREATE_ERROR), 1);
		i++;
	}
	return (0);
}

/*Waits for all the threads to finish.*/
void	reaper(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_philos)
	{
		if (pthread_join(philo[i].th, NULL) != 0)
			return ;
		i++;
	}
}
