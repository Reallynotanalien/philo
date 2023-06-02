/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:55:50 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/02 18:29:57 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (data->num_philos > i)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
}

void	destroy_and_free_data(t_data *data)
{
	destroy_forks(data);
	pthread_mutex_destroy(data->write_access);
	pthread_mutex_destroy(data->death);
	pthread_mutex_destroy(data->full);
	pthread_mutex_destroy(data->time);
	free(data->fork);
	free(data->write_access);
	free(data->death);
	free(data->full);
	free(data->time);
	free(data);
}
