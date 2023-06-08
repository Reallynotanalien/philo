/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:39:31 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/07 21:36:20 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Changes both the philo status and the data status to FULL to let the
undertaker know everyone is full. To avoid data races, we need to lock the 
data->status variable so it is not accessible to others at the same time by
locking the status_check mutex.*/
void	change_status_to_full(t_philo *philo)
{
	pthread_mutex_lock(philo->data->status_check);
	philo->status = FULL;
	philo->data->status = FULL;
	pthread_mutex_unlock(philo->data->status_check);
	pthread_mutex_lock(philo->data->write_access);
	printf("%li %s", get_time_in_ms(philo), STOP_EATING);
	pthread_mutex_unlock(philo->data->write_access);
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

/*Checks if the philo has eaten the number of meals that he should. If
he did not, increments philo->meals to let the program know he ate one more
time. If he did, the philo status is changed to FULL and the number of full
philos is incremented.*/
void	check_number_of_meals(t_philo *philo)
{
	if (philo->total_meals > philo->meals)
	{
		pthread_mutex_lock(philo->data->meals);
		philo->meals++;
		pthread_mutex_unlock(philo->data->meals);
	}
	else if (philo->total_meals == philo->meals)
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

/*Before locking the right fork, checks if the simulation should be
over (due to a philo dying) and checks if the philo is dead(if it took
too long to eat). The right fork is locked and the fork message is
printed. Same process for the left fork, except that if the number of
philos is one, this is where he will die or else he will be waiting 
for the left fork forever.
The philo->timer variable is now adjusted to keep track of the philo's
last meal.*/
void	take_forks(t_philo *philo)
{
	if (check_if_someone_died(philo) != DEAD
		&& check_if_dead(philo) != DEAD)
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(FORK, philo);
		if (philo->data->num_philos == 1)
		{
			waiting(philo->die);
			change_status_to_dead(philo);
			return ;
		}
		pthread_mutex_lock(philo->left_fork);
		print_message(FORK, philo);
	}
	pthread_mutex_lock(philo->data->time);
	philo->timer = get_time();
	pthread_mutex_unlock(philo->data->time);
}

/*Locks the right fork, then locks the left fork and starts the timer
to know when was the last meal. The philo starts eating for the duration
of the time_to_eat variable then unlocks the forks, before checking if 
the philo is full.*/
void	eating(t_philo *philo)
{
	take_forks(philo);
	if (check_philo_status(philo) != DEAD
		&& check_philo_status(philo) != FULL)
	{
		print_message(EAT, philo);
		waiting(philo->eat);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->total_meals != 0)
		check_number_of_meals(philo);
}
