/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:55:50 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/16 14:58:50 by kafortin         ###   ########.fr       */
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
