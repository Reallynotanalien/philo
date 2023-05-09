/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:20:04 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/09 18:32:26 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	waiting(long int ms)
{
	long int	wait_until;

	wait_until = get_time() + ms;
	while (1)
	{
		if (get_time() >= wait_until)
			return ;
		usleep(50);
	}
}

void	thinking(t_philo *philo)
{
	printf("%li %i %s", (get_time() - philo->data->beginning), philo->id, THINK);
}

void	sleeping(t_philo *philo)
{
	printf("%li %i %s", (get_time() - philo->data->beginning), philo->id, SLEEP);
	waiting(philo->data->time_to_sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printf("%li %i %s", (get_time() - philo->data->beginning), philo->id, FORK);
	pthread_mutex_lock(philo->left_fork);
	printf("%li %i %s", (get_time() - philo->data->beginning), philo->id, FORK);
	printf("%li %i %s", (get_time() - philo->data->beginning), philo->id, EAT);
	waiting(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*life_of_a_philo(void *i)
{
	t_philo		*philo;

	philo = (t_philo *)i;
	while (philo->status != END)
	{
		if (philo->data->num_meals != 0)
		{
			if(philo->data->num_meals > philo->meals)
				philo->meals++;
			else if (philo->data->num_meals == philo->meals)
				philo->status = END;
		}
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	/*Philos think between eating and sleeping. If there is no delay between the two, he still thinks but then starts eating right away.*/
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data			*data;
	t_philo			*philo;
	pthread_mutex_t	lock;
	int				i;

	if (argc > 6 || argc < 5)
		exit_error(ARG_NUM_ERROR);
	data = malloc(sizeof(t_data));
	init_data(argc, argv, data);
	philo = malloc(sizeof(t_philo) * data->num_philos);
	pthread_mutex_init(&lock, NULL);
	init_forks(data);
	init_philos(philo, data);
	i = 0;
	while (data->num_philos > i)
	{
		if (pthread_join(philo[i].th, NULL) != 0)
			exit_error("Thread join error\n");
		data->now = get_time();
		data->now -= data->beginning;
		free(&philo[i]);
		i++;
	}
	free(philo);
	pthread_mutex_destroy(&lock);
	/*If there is only one philosopher, the program must run until he dies because he only has one fork*/
	/*Timer for last meal starts as soon as the philo starts to eat*/
}
