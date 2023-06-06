/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:36:21 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/06 15:39:21 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		philo[i].num_philos = data->num_philos;
		//philo.num_philo really necessary?
		philo[i].timer = 0;
		philo[i].right_fork = &data->fork[i];
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
		if (pthread_create(&philo[i].th, NULL, &life_of_a_philo,
				&philo[i]) != 0)
			return (destroy_and_free_data(data), free(philo),
				error_message(THREAD_CREATE_ERROR), 1);
		i++;
	}
	return (0);
}

void	wait_for_philos(t_philo *philo)
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
