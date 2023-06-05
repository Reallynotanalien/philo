/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:41:07 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/05 14:55:19 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_message(char *message, t_philo *philo)
{
	if (check_if_someone_died(philo) != DEAD)
	{
		pthread_mutex_lock(philo->data->write_access);
		printf("%li %i %s", (get_time() - philo->data->beginning),
			philo->id, message);
		pthread_mutex_unlock(philo->data->write_access);
	}
	else if (ft_strcmp(message, DIE) == 0)
	{
		pthread_mutex_lock(philo->data->write_access);
		printf("%li %i %s", (get_time() - philo->data->beginning),
			philo->id, message);
		pthread_mutex_unlock(philo->data->write_access);
	}
}

int	check_if_full(t_philo *philo)
{
	if (philo->data->num_meals != 0)
	{
		if (philo->data->num_meals >= philo->meals)
			philo->meals++;
		else if (philo->data->num_meals < philo->meals)
		{
			pthread_mutex_lock(philo->data->death);
			philo->status = END;
			pthread_mutex_unlock(philo->data->death);
		}
	}
	return (philo->status);
}

int	check_if_anyone_is_dead(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(philo->data->death);
	state = philo->data->status;
	pthread_mutex_unlock(philo->data->death);
	return (state);
}

void	thinking(t_philo *philo)
{
	if (check_if_anyone_is_dead(philo) != DEAD)
		print_message(THINK, philo);
}

void	sleeping(t_philo *philo)
{
	if (check_if_anyone_is_dead(philo) != DEAD)
	{
		print_message(SLEEP, philo);
		waiting(philo->data->time_to_sleep);
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

void	eating(t_philo *philo)
{
	//philo must check if both forks are accessible before taking them.
	// check_if_dead(philo);
	if (check_if_anyone_is_dead(philo) != DEAD)
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(FORK, philo);
	}
	if (check_if_anyone_is_dead(philo) != DEAD)
	{
		if (philo->num_philos == 1)
		{
			waiting(philo->data->time_to_die);
			change_status(philo);
			return ;
		}
		pthread_mutex_lock(philo->left_fork);
		print_message(FORK, philo);
		pthread_mutex_lock(philo->data->time);
		philo->timer = get_time();
		pthread_mutex_unlock(philo->data->time);
		print_message(EAT, philo);
		waiting(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (philo->data->num_meals != 0)
		{
			if (philo->data->num_meals > philo->meals)
				philo->meals++;
			else if (philo->data->num_meals == philo->meals)
			{
				pthread_mutex_lock(philo->data->full);
				philo->status = END;
				philo->meals++;
				philo->data->full_philos++;
				pthread_mutex_unlock(philo->data->full);
			}
		}
	}
}

void	*life_of_a_philo(void *i)
{
	t_philo	*philo;

	philo = (t_philo *)i;
	if (philo->id % 2 == 0)
		usleep(15000);
	// while ((check_if_full(philo) != END || philo->data->num_meals == 0)
	// 	&& philo->data->status != DEAD)
	while (check_if_anyone_is_dead(philo) != DEAD
		&& check_if_everyone_is_full(philo) != END)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
