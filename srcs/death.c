/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:33:50 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/07 20:20:38 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	change_status_to_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->data->status_check);
	philo->status = DEAD;
	philo->data->status = DEAD;
	pthread_mutex_unlock(philo->data->status_check);
}

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

int	check_if_dead(t_philo *philo)
{
	long int	now;
	long int	last_meal;
	int			status;

	now = get_time();
	status = check_philo_status(philo);
	if ((philo->num % 2 == 0 && philo->die < (philo->eat * 2))
		|| (philo->num % 2 != 0 && philo->die < (philo->eat * 3))
		|| philo->die < philo->eat + philo->sleep)
		if (get_time_in_ms(philo) >= philo->die)
			change_status_to_dead(philo);
	if (status != DEAD)
	{
		pthread_mutex_lock(philo->data->time);
		last_meal = philo->timer;
		pthread_mutex_unlock(philo->data->time);
		if (last_meal != 0)
		{
			if (now - last_meal >= philo->data->time_to_die)
			{
				if ((philo->num % 2 == 0 && philo->die < (philo->eat * 2))
					|| (philo->num % 2 != 0 && philo->die < (philo->eat * 3))
					|| philo->die < philo->eat + philo->sleep)
					change_status_to_dead(philo);
			}
		}
	}
	return (status);
}

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
			// if (check_if_someone_died(&philo[i]) == DEAD)
			// {
			// 	print_message(DIE, philo);
			// 	return ;
			// }
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
