/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:41:07 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/29 19:19:58 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*keeper_of_status(void *status)
{
	static void	*last_status = NULL;

	if (status)
		last_status = status;
	return (last_status);
}

void	print_message(char *message, t_philo *philo)
{
	//printer must check if all philos are alive before printing a message.
	if (philo->status != END && philo->status != IDLE && philo->status != DEAD)
	{
		pthread_mutex_lock(philo->data->death);
		if (philo->data->status != DEAD)
		{
			pthread_mutex_lock(philo->data->write_access);
			printf("%li %i %s", (get_time() - philo->data->beginning),
				philo->id, message);
			pthread_mutex_unlock(philo->data->write_access);
		}
		pthread_mutex_unlock(philo->data->death);
	}
	else if (philo->status == END)
	{
		pthread_mutex_lock(philo->data->death);
		if (philo->data->status != DEAD)
		{
			pthread_mutex_lock(philo->data->write_access);
			printf("%i had enough to eat! %i meals is enough.\n", philo->id, philo->meals);
			philo->meals++;
			philo->status = IDLE;
			pthread_mutex_unlock(philo->data->write_access);
		}
		pthread_mutex_unlock(philo->data->death);
		//this is temporary, just to make sure the printing stops if all the
		//philo ate enough times.
	}
	else if (philo->status == DEAD)
	{
		pthread_mutex_lock(philo->data->write_access);
		printf("%li %i %s", (get_time() - philo->data->beginning), philo->id,
			message);
		pthread_mutex_lock(philo->data->death);
		philo->status = IDLE;
		pthread_mutex_unlock(philo->data->death);
		pthread_mutex_unlock(philo->data->write_access);
	}
}

int	check_if_dead(t_philo *philo)
{
	long int	now;

	pthread_mutex_lock(philo->data->death);
	now = get_time();
	if (philo->timer != 0 && now - philo->timer >= philo->data->time_to_die)
	{
		philo->status = DEAD;
		philo->data->status = DEAD;
	}
	pthread_mutex_unlock(philo->data->death);
	return (philo->status);
}

void	thinking(t_philo *philo)
{
	// if (check_if_dead(philo) == DEAD)
	// 	print_message(DIE, philo);
	print_message(THINK, philo);
}

void	sleeping(t_philo *philo)
{
	// if (check_if_dead(philo) == DEAD)
	// 	print_message(DIE, philo);
	print_message(SLEEP, philo);
	waiting(philo->data->time_to_sleep);
}

void	eating(t_philo *philo)
{
	//philo must check if both forks are accessible before taking them.
	if (check_if_dead(philo) == DEAD)
		print_message(DIE, philo);
	pthread_mutex_lock(philo->right_fork);
	print_message(FORK, philo);
	pthread_mutex_lock(philo->left_fork);
	print_message(FORK, philo);
	philo->timer = get_time();
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
			pthread_mutex_lock(philo->data->death);
			philo->status = END;
			pthread_mutex_unlock(philo->data->death);
		}
	}
}

void	*life_of_a_philo(void *i)
{
	t_philo	*philo;

	philo = (t_philo *)i;
	if (philo->id % 2 == 0)
		usleep(15000);
	while ((philo->meals <= philo->data->num_meals
		|| philo->data->num_meals == 0) && philo->data->status != DEAD)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
