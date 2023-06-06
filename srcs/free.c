/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:55:50 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/06 15:32:33 by kafortin         ###   ########.fr       */
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

void	destroy_mutexes(t_data *data)
{
	if (data->write_access)
		pthread_mutex_destroy(data->write_access);
	if (data->status_check)
		pthread_mutex_destroy(data->status_check);
	if (data->meals)
		pthread_mutex_destroy(data->meals);
	if (data->time)
		pthread_mutex_destroy(data->time);
}

void	free_all(t_data *data)
{
	if (data->fork == NULL)
		return ;
	else
		free(data->fork);
	if (data->write_access == NULL)
		return ;
	else
		free(data->write_access);
	if (data->status_check == NULL)
		return ;
	else
		free(data->status_check);
	if (data->meals == NULL)
		return ;
	else
		free(data->meals);
	if (data->time == NULL)
		return ;
	else
		free(data->time);
}

void	destroy_and_free_data(t_data *data)
{
	destroy_forks(data);
	destroy_mutexes(data);
	free_all(data);
	free(data);
}
