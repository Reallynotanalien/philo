/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:33:50 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/05 16:55:51 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	change_status(t_philo *philo)
{
	pthread_mutex_lock(philo->data->death);
	philo->status = DEAD;
	philo->data->status = DEAD;
	pthread_mutex_unlock(philo->data->death);
	print_message(DIE, philo);
}

int	check_status(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->data->death);
	status = philo->status;
	pthread_mutex_unlock(philo->data->death);
	return (status);
}

int	check_if_someone_died(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->data->death);
	status = philo->data->status;
	pthread_mutex_unlock(philo->data->death);
	return (status);
}

int	check_if_dead(t_philo *philo)
{
	long int	now;
	int			status;

	now = get_time();
	status = check_status(philo);
	pthread_mutex_lock(philo->data->time);
	if (philo->timer != 0 && now - philo->timer >= philo->data->time_to_die)
	{
		if (status != DEAD)
			change_status(philo);
		// philo->death_time = now - philo->timer;
		// printf("%li %i %s", (get_time() - philo->data->beginning),
		// 	philo->id, DIE);
	}
	pthread_mutex_unlock(philo->data->time);
	return (status);
}

void	undertaker(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (check_if_dead(&philo[i]) == DEAD)
			return ;
		if (check_if_someone_died(&philo[i]) == DEAD)
			return ;
		if (check_if_everyone_is_full(philo) == END)
		{
			print_message(FULL, philo);
			return ;
		}
		i++;
		if (i == data->num_philos)
			i = 0;
	}
}
