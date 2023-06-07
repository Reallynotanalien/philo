/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:39:31 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/07 18:36:58 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	change_status_to_full(t_philo *philo)
{
	pthread_mutex_lock(philo->data->status_check);
	philo->status = FULL;
	philo->data->status = FULL;
	pthread_mutex_unlock(philo->data->status_check);
	print_message(STOP_EATING, philo);
}

/*Checks the number of full philos and if it is the same as the number of
philos, returns FULL. To avoid data races we need to lock the data->full_philos
variable so it is not accessible to others at the same time by locking the 
data->meals mutex.*/
int	check_if_everyone_is_full(t_philo *philo)
{
	int	state;

	state = 0;
	pthread_mutex_lock(philo->data->meals);
	if (philo->data->full_philos == philo->data->num_philos)
		state = FULL;
	pthread_mutex_unlock(philo->data->meals);
	return (state);
}

void	check_number_of_meals(t_philo *philo)
{
	if (philo->data->num_meals != 0)
	{
		if (philo->data->num_meals > philo->meals)
		{
			pthread_mutex_lock(philo->data->meals);
			philo->meals++;
			pthread_mutex_unlock(philo->data->meals);
		}
		else if (philo->data->num_meals == philo->meals)
		{
			pthread_mutex_lock(philo->data->status_check);
			philo->status = FULL;
			pthread_mutex_unlock(philo->data->status_check);
			pthread_mutex_lock(philo->data->meals);
			philo->meals++;
			philo->data->full_philos++;
			pthread_mutex_unlock(philo->data->meals);
		}
	}
}

/*Before locking the right fork, checks if the simulation should be
over (due to a philo dying) and checks if the philo is dead(if it took
too long to eat). The right fork is locked and the fork message is
printed. Same process for the left fork, except that if the number of
philos is one, this is where he will die or else he will be waiting 
for the left fork forever.*/
void	take_forks(t_philo *philo)
{
	if (check_if_someone_died(philo) != DEAD
		&& check_if_dead(philo) != DEAD)
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(FORK, philo);
	}
	if (check_if_someone_died(philo) != DEAD
		&& check_if_dead(philo) != DEAD)
	{
		if (philo->data->num_philos == 1)
		{
			waiting(TIME_TO_DIE, philo);
			change_status_to_dead(philo);
			return ;
		}
		pthread_mutex_lock(philo->left_fork);
		print_message(FORK, philo);
	}
}

/*Locks the right fork, then locks the left fork and starts the timer
to know when was the last meal. The philo starts eating for the duration
of the time_to_eat variable then unlocks the forks, before checking if 
the philo is full.*/
void	eating(t_philo *philo)
{
	take_forks(philo);
	adjust_timer(philo);
	print_message(EAT, philo);
	waiting(TIME_TO_EAT, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	check_number_of_meals(philo);
}
