/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:46:55 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/07 21:45:55 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Gets the actual time from the system.*/
long int	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

/*Translates the time from get_time in ms by substracting the beginning time.*/
long int	get_time_in_ms(t_philo *philo)
{
	long int	now;

	pthread_mutex_lock(philo->data->time);
	now = get_time() - philo->data->beginning;
	pthread_mutex_unlock(philo->data->time);
	return (now);
}

/*Waits until the time sent as an argument has passed.*/
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

/*Checks if a philo is destined to die by looking at the time to die and 
comparing it with the other data. If time to eat and sleep surpasses the time
to die, or if the philo doesn't have time to eat AND wait for his neighboor to
eat before the times to die expires, then returns DEAD.*/
int	destiny_checker(t_philo *philo)
{
	int	destiny;

	destiny = 0;
	if ((philo->num % 2 == 0 && philo->die < (philo->eat * 2))
		|| (philo->num % 2 != 0 && philo->die < (philo->eat * 3))
		|| philo->die < philo->eat + philo->sleep)
		destiny = DEAD;
	return (destiny);
}
