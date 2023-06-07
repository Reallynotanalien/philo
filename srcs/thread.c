/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:41:07 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/07 16:00:58 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_message(char *message, t_philo *philo)
{
	if (check_if_someone_died(philo) != DEAD
		&& check_if_everyone_is_full(philo) != FULL
		&& get_time() > philo->data->death_time)
	{
		pthread_mutex_lock(philo->data->write_access);
		if (get_time() > philo->data->death_time)
			printf("%li %i %s", get_time_in_ms(philo), philo->id, message);
		pthread_mutex_unlock(philo->data->write_access);
	}
	else if (ft_strcmp(message, DIE) == 0)
	{
		pthread_mutex_lock(philo->data->write_access);
		printf("%li %i %s", get_time_in_ms(philo), philo->id, message);
		pthread_mutex_unlock(philo->data->write_access);
	}
	else if (ft_strcmp(message, STOP_EATING) == 0)
	{
		pthread_mutex_lock(philo->data->write_access);
		printf("%li %s", get_time_in_ms(philo), message);
		pthread_mutex_unlock(philo->data->write_access);
	}
}

void	thinking(t_philo *philo)
{
	if (check_if_someone_died(philo) != DEAD)
		if (check_if_dead(philo) != DEAD)
			print_message(THINK, philo);
}

void	sleeping(t_philo *philo)
{
	if (check_if_someone_died(philo) != DEAD)
	{
		if (check_if_dead(philo) != DEAD)
		{
			print_message(SLEEP, philo);
			waiting(TIME_TO_SLEEP, philo);
		}
	}
}

/*This is the philosophers routine, each thread will complete it.
Since we need the t_philo struct, we will need to create a copy of
it to be able to use it since we sent a void * to the function. Then,
there is a delay for all philos with a number that is divided by 2 so
that they won't try to take all their forks at the same time.
The routine then starts and will go on until a philosopher dies or
everyone is full. They eat, sleep and think.*/
void	*life_of_a_philo(void *i)
{
	t_philo	*philo;

	philo = (t_philo *)i;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (check_if_someone_died(philo) != DEAD
		&& check_if_everyone_is_full(philo) != FULL)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
