/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:39:31 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/05 17:26:50 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	change_full_status(t_philo *philo)
{
	pthread_mutex_lock(philo->data->full);
	pthread_mutex_lock(philo->data->death);
	philo->status = END;
	philo->data->status = END;
	pthread_mutex_unlock(philo->data->full);
	pthread_mutex_unlock(philo->data->death);
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

void	check_number_of_meals(t_philo *philo)
{
	if (philo->data->num_meals != 0)
	{
		if (philo->data->num_meals > philo->meals)
			philo->meals++;
		else if (philo->data->num_meals == philo->meals)
		{
			pthread_mutex_lock(philo->data->full);
			pthread_mutex_lock(philo->data->death);
			philo->status = END;
			pthread_mutex_unlock(philo->data->death);
			philo->meals++;
			philo->data->full_philos++;
			pthread_mutex_unlock(philo->data->full);
		}
	}
}

void	take_forks(t_philo *philo)
{
	if (check_if_someone_died(philo) != DEAD)
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(FORK, philo);
	}
	if (check_if_someone_died(philo) != DEAD)
	{
		if (philo->num_philos == 1)
		{
			waiting(TIME_TO_DIE, philo);
			change_status(philo);
			return ;
		}
		pthread_mutex_lock(philo->left_fork);
		print_message(FORK, philo);
	}
}

void	eating(t_philo *philo)
{
	//philo must check if both forks are accessible before taking them.
	// check_if_dead(philo);
	take_forks(philo);
	adjust_timer(philo);
	print_message(EAT, philo);
	waiting(TIME_TO_EAT, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	check_number_of_meals(philo);
}
