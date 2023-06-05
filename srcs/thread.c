/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:41:07 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/05 16:59:10 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_message(char *message, t_philo *philo)
{
	if (check_if_someone_died(philo) != DEAD
		&& check_if_everyone_is_full(philo) != END)
	{
		pthread_mutex_lock(philo->data->write_access);
		pthread_mutex_lock(philo->data->time);
		printf("%li %i %s", (get_time() - philo->data->beginning),
			philo->id, message);
		pthread_mutex_unlock(philo->data->write_access);
		pthread_mutex_unlock(philo->data->time);
	}
	else if (ft_strcmp(message, DIE) == 0)
	{
		pthread_mutex_lock(philo->data->write_access);
		pthread_mutex_lock(philo->data->time);
		printf("%li %i %s", (get_time() - philo->data->beginning),
			philo->id, message);
		pthread_mutex_unlock(philo->data->write_access);
		pthread_mutex_unlock(philo->data->time);
	}
	else if (ft_strcmp(message, FULL) == 0)
	{
		pthread_mutex_lock(philo->data->write_access);
		pthread_mutex_lock(philo->data->time);
		printf("%li %s", (get_time() - philo->data->beginning), message);
		pthread_mutex_unlock(philo->data->write_access);
		pthread_mutex_unlock(philo->data->time);
	}
}

void	thinking(t_philo *philo)
{
	if (check_if_someone_died(philo) != DEAD)
		print_message(THINK, philo);
}

void	sleeping(t_philo *philo)
{
	if (check_if_someone_died(philo) != DEAD)
	{
		print_message(SLEEP, philo);
		waiting(TIME_TO_SLEEP, philo);
	}
}

int	check_if_everyone_is_full(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(philo->data->full);
	state = 0;
	if (philo->data->full_philos == philo->data->num_philos)
		state = END;
	pthread_mutex_unlock(philo->data->full);
	return (state);
}

void	*life_of_a_philo(void *i)
{
	t_philo	*philo;

	philo = (t_philo *)i;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (check_if_someone_died(philo) != DEAD
		&& check_if_everyone_is_full(philo) != END)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
