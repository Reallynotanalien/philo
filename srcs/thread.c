/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:41:07 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/19 18:16:26 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_message(char *message, t_philo *philo)
{
	//printer must check if all philos are alive before printing a message.
	pthread_mutex_lock(philo->data->write_access);
	printf("%li %i %s", (get_time() - philo->data->beginning),
		philo->id, message);
	pthread_mutex_unlock(philo->data->write_access);
}

void	sleeping(t_philo *philo)
{
	print_message(SLEEP, philo);
	waiting(philo->data->time_to_sleep);
}

void	eating(t_philo *philo)
{
	//philo must check if both forks are accessible before taking them.
	pthread_mutex_lock(philo->right_fork);
	print_message(FORK, philo);
	pthread_mutex_lock(philo->left_fork);
	print_message(FORK, philo);
	philo->timer = get_time();
	print_message(EAT, philo);
	waiting(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*life_of_a_philo(void *i)
{
	t_philo	*philo;

	philo = (t_philo *)i;
	if (philo->id % 2 == 0)
		usleep(15);
	while (1)
	{
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}
