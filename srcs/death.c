/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:33:50 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/07 21:31:11 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Changes both the philo status and the data status to DEAD to let the 
undertaker know someone died. To avoid data races, we need to lock the
data->status variable so it is not accessible to others at the same time by
locking the status_check mutex.*/
void	change_status_to_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->data->status_check);
	philo->status = DEAD;
	philo->data->status = DEAD;
	pthread_mutex_unlock(philo->data->status_check);
}

/*Checks the philo status, which is updated when a specific philosopher dies,
and returns it. To avoid data races we need to lock the data->status
variable so it is not accessible to others at the same time by locking the
status_check mutex.*/
int	check_philo_status(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->data->status_check);
	status = philo->status;
	pthread_mutex_unlock(philo->data->status_check);
	return (status);
}

/*Checks the data status, which is updated when one philosopher dies, and
returns it. To avoid data races we need to lock the data->status variable
so it is not accessible to others at the same time by locking the
status_check mutex.*/
int	check_if_someone_died(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->data->status_check);
	status = philo->data->status;
	pthread_mutex_unlock(philo->data->status_check);
	return (status);
}

/*Checks if the philo is supposed to die according to the parameters that
were sent to the program and corroborates if the actual time is up. If it is,
it means the philo is dead. 
To reinforce the verifications, if the status is not yet to DEAD, checks if
the timer since last meal is bigger than the time_to_die variable. If it is,
it means the philo is dead.
If the philo is dead according to any of these tests, changes the status to
dead to let the undertaker know.*/
int	check_if_dead(t_philo *philo)
{
	long int	now;
	long int	last_meal;
	int			status;

	now = get_time();
	status = check_philo_status(philo);
	if (destiny_checker(philo) == DEAD)
		if (get_time_in_ms(philo) >= philo->die)
			change_status_to_dead(philo);
	if (status != DEAD)
	{
		pthread_mutex_lock(philo->data->time);
		last_meal = philo->timer;
		pthread_mutex_unlock(philo->data->time);
		if (last_meal != 0)
		{
			if (now - last_meal >= philo->die)
			{
				if (destiny_checker(philo) == DEAD)
					change_status_to_dead(philo);
			}
		}
	}
	return (status);
}

/*Iterates through all philosophers one by one to check if any of them
is dead. If it is, prints the death message and exits the function.
If nobody is dead yet, checks if everyone is full before restarting the
loop. If everyone is full, exits the function.*/
void	undertaker(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		while (i < data->num_philos)
		{
			if (check_if_dead(&philo[i]) == DEAD)
			{
				pthread_mutex_lock(philo->data->write_access);
				printf("%i %i %s", philo->die, philo->id, DIE);
				pthread_mutex_unlock(philo->data->write_access);
				return ;
			}
			i++;
		}
		if (check_if_everyone_is_full(philo) == FULL)
		{
			change_status_to_full(philo);
			return ;
		}
		if (i == data->num_philos)
			i = 0;
	}
}
