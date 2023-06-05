/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:36:21 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/05 14:54:54 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philo_data(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (data->num_philos > i)
	{
		philo[i].id = i + 1;
		philo[i].status = 0;
		philo[i].meals = 1;
		philo[i].right_fork = &data->fork[i];
		philo[i].death_time = 0;
		philo[i].num_philos = data->num_philos;
		i++;
	}
}

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
		philo[i].data = data;
		if (pthread_create(&philo[i].th, NULL, &life_of_a_philo,
				&philo[i]) != 0)
			return (destroy_and_free_data(data), free(philo),
				error_message(THREAD_CREATE_ERROR), 1);
		i++;
	}
	return (0);
}
