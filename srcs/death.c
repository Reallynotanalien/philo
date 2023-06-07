/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:33:50 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/07 18:45:20 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	change_status_to_dead(t_philo *philo)
{
	// if (check_if_someone_died(philo) != DEAD)
	// 	print_message(DIE, philo);
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
	int			status;

	now = get_time();
	status = check_philo_status(philo);
	if ((philo->data->num_philos % 2 == 0 && philo->data->time_to_die
			<= (philo->data->time_to_eat * 2))
		|| (philo->data->num_philos % 2 != 0 && philo->data->time_to_die
			<= (philo->data->time_to_eat * 3))
		|| philo->data->time_to_die <= philo->data->time_to_eat
		+ philo->data->time_to_sleep)
	{
		if (check_timer(philo) != 0
			&& now - check_timer(philo) >= philo->data->time_to_die)
		{
			if (status != DEAD && status != FULL)
				change_status_to_dead(philo);
		}
	}
	return (status);
}

int	check_if_dead2(t_philo *philo, t_data *data)
{
	long int	now;
	int			status;

	now = get_time();
	status = check_philo_status(philo);
	if ((philo->data->num_philos % 2 == 0 && philo->data->time_to_die
			<= (philo->data->time_to_eat * 2))
		|| (philo->data->num_philos % 2 != 0 && philo->data->time_to_die
			<= (philo->data->time_to_eat * 3))
		|| philo->data->time_to_die <= philo->data->time_to_eat
		+ philo->data->time_to_sleep)
	{
		if (check_timer(philo) != 0
			&& now - check_timer(philo) >= philo->data->time_to_die)
		{
			if (status != DEAD && status != FULL)
			{
				pthread_mutex_lock(philo->data->status_check);
				philo->status = DEAD;
				data->status = DEAD;
				pthread_mutex_unlock(philo->data->status_check);
			}
		}
	}
	return (status);
}

void	kill_everyone(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philo->data->status_check);
	while (i < data->num_philos)
	{
		philo[i].status = DEAD;
		philo[i].data->status = DEAD;
		i++;
	}
	pthread_mutex_unlock(philo->data->status_check);
}

void	undertaker(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (check_if_dead2(&philo[i], data) == DEAD)
		{
			print_message(DIE, philo);
			// kill_everyone(philo, data);
			return ;
		}
		// if (check_if_someone_died(&philo[i]) == DEAD)
		// {
		// 	kill_everyone(philo, data);
		// 	return ;
		// }
		if (check_if_everyone_is_full(philo) == FULL)
		{
			change_status_to_full(philo);
			return ;
		}
		i++;
		if (i == data->num_philos)
			i = 0;
	}
}
