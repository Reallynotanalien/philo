/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:41:07 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/07 20:15:44 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Prints the message sent as an argument, but only if the simulation is still
going on! To make sure it is, this function checks if someone died or if
everyone is full before printing anything. Since we do not want messages from
multiple threads printing at the same time, we need to lock the write_access
mutex before printing.*/
void	print_message(char *message, t_philo *philo)
{
	if (check_if_someone_died(philo) != DEAD
		&& check_if_everyone_is_full(philo) != FULL)
	{
		pthread_mutex_lock(philo->data->write_access);
		printf("%li %i %s", get_time_in_ms(philo), philo->id, message);
		pthread_mutex_unlock(philo->data->write_access);
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
		print_message(SLEEP, philo);
		waiting(philo->sleep);
		print_message(THINK, philo);
	}
	return (NULL);
}
