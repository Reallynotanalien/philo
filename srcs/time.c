/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:46:55 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/07 20:03:16 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

long int	get_time_in_ms(t_philo *philo)
{
	long int	now;

	pthread_mutex_lock(philo->data->time);
	now = get_time() - philo->data->beginning;
	pthread_mutex_unlock(philo->data->time);
	return (now);
}

void	waiting(int time)
{
	long int	wait_until;
	long int	ms;

	ms = time;
	wait_until = get_time() + ms;
	while (1)
	{
		if (get_time() >= wait_until)
			return ;
		usleep(1000);
	}
}
