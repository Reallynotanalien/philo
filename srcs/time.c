/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:46:55 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/06 16:51:38 by kafortin         ###   ########.fr       */
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

void	waiting(int time, t_philo *philo)
{
	long int	wait_until;
	long int	ms;

	ms = 0;
	pthread_mutex_lock(philo->data->time);
	if (time == TIME_TO_DIE)
		ms = philo->data->time_to_die;
	else if (time == TIME_TO_EAT)
		ms = philo->data->time_to_eat;
	else if (time == TIME_TO_SLEEP)
		ms = philo->data->time_to_sleep;
	pthread_mutex_unlock(philo->data->time);
	wait_until = get_time() + ms;
	while (1)
	{
		if (get_time() >= wait_until)
			return ;
		usleep(50);
	}
}

long int	check_timer(t_philo *philo)
{
	long int	check;

	pthread_mutex_lock(philo->data->time);
	check = philo->timer;
	pthread_mutex_unlock(philo->data->time);
	return (check);
}

void	adjust_timer(t_philo *philo)
{
	pthread_mutex_lock(philo->data->time);
	philo->timer = get_time();
	pthread_mutex_unlock(philo->data->time);
}
