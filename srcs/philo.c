/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:20:04 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/12 16:31:27 by kafortin         ###   ########.fr       */
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
	pthread_mutex_lock(philo->data->write_access);
	printf("%li %i %s", (get_time() - philo->data->beginning), philo->id, THINK);
	pthread_mutex_unlock(philo->data->write_access);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->data->write_access);
	printf("%li %i %s", (get_time() - philo->data->beginning), philo->id, SLEEP);
	pthread_mutex_unlock(philo->data->write_access);
	waiting(philo->data->time_to_sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->data->write_access);
	printf("%li %i %s", (get_time() - philo->data->beginning), philo->id, FORK);
	pthread_mutex_unlock(philo->data->write_access);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->data->write_access);
	printf("%li %i %s", (get_time() - philo->data->beginning), philo->id, FORK);
	pthread_mutex_unlock(philo->data->write_access);
	pthread_mutex_lock(philo->data->write_access);
	philo->timer = get_time();
	printf("%li %i %s", (get_time() - philo->data->beginning), philo->id, EAT);
	pthread_mutex_unlock(philo->data->write_access);
	waiting(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	check_if_dead(t_philo *philo)
{
	int			dead;
	long int	now;

	pthread_mutex_lock(philo->data->death);
	now = get_time();
	if (philo->timer != 0 && now - philo->timer >= philo->data->time_to_die)
	{
		philo->status = DEAD;
		philo->data->status = DEAD;
	}
	dead = philo->status;
	pthread_mutex_unlock(philo->data->death);
	return (dead);
}

int	check_if_full(t_philo *philo)
{
	int	full;

	pthread_mutex_lock(philo->data->full);
	full = philo->status;
	pthread_mutex_unlock(philo->data->full);
	return (full);
}

void	*life_of_a_philo(void *i)
{
	t_philo		*philo;

	philo = (t_philo *)i;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (check_if_dead(philo) != DEAD && check_if_full(philo) != END)
	{
		if (philo->data->num_meals != 0)
		{
			if(philo->data->num_meals > philo->meals)
			{
				pthread_mutex_lock(philo->data->write_access);
				philo->meals++;
				pthread_mutex_unlock(philo->data->write_access);
			}
			else if (philo->data->num_meals == philo->meals)
				philo->status = END;
		}
		eating(philo);
		pthread_mutex_lock(philo->data->death);
		if (philo->status != DEAD && philo->data->status == DEAD)
			return(NULL);
		pthread_mutex_unlock(philo->data->death);
		sleeping(philo);
		pthread_mutex_lock(philo->data->death);
		if (philo->status != DEAD && philo->data->status == DEAD)
			return(NULL);
		pthread_mutex_unlock(philo->data->death);
		thinking(philo);
		pthread_mutex_lock(philo->data->death);
		if (philo->status != DEAD && philo->data->status == DEAD)
			return(NULL);
		pthread_mutex_unlock(philo->data->death);
	}
	if (philo->status == DEAD)
	{
		pthread_mutex_lock(philo->data->write_access);
		printf("%li %i %s", (get_time() - philo->data->beginning), philo->id, DIE);
		pthread_mutex_unlock(philo->data->write_access);
	}
	/*Philos think between eating and sleeping. If there is no delay between the two, he still thinks but then starts eating right away.*/
	return (NULL);
}

// void	*check_on_philos(void *p)
// {
// 	t_philo			*philo;

// 	philo = (t_philo *)p;
// 	while (1)
// 	{
// 		pthread_mutex_lock(philo->data->death);
// 		if (philo->status == DEAD)
// 		{
// 			pthread_mutex_lock(philo->data->write_access);
// 			printf("%li %i %s", (get_time() - philo->data->beginning), 1, DIE);
// 			pthread_mutex_unlock(philo->data->write_access);
// 		}
// 		pthread_mutex_unlock(philo->data->death);
// 	}
// 	return (NULL);
// }

int	maine(int argc, char **argv)
{
	t_data			*data;
	t_philo			*philo;
	int				i;
	// pthread_t		guardian;

	if (argc > 6 || argc < 5)
		error_message(ARG_NUM_ERROR);
	data = malloc(sizeof(t_data));
	init_data(argc, argv, data);
	philo = malloc(sizeof(t_philo) * data->num_philos);
	init_forks(data);
	init_philos(philo, data);
	i = 0;
	// if (pthread_create(&guardian, NULL, &check_on_philos, &philo) != 0)
	// 	error_message("Thread error\n");
	// pthread_detach(guardian);
	while (data->num_philos > i)
	{
		if (pthread_join(philo[i].th, NULL) != 0)
			error_message("Thread join error\n");
		data->now = get_time();
		data->now -= data->beginning;
		free(&philo[i]);
		i++;
	}
	/*Make it so that if a philosopher dies before everyone eats, this phrase does not appear.*/
	pthread_mutex_lock(philo->data->write_access);
	if (philo->data->status == END)
		printf("Each philosophers ate %i times. They are full now!\n", philo->meals);
	pthread_mutex_unlock(philo->data->write_access);
	// free(philo);
	// pthread_mutex_destroy(&death);
	/*If there is only one philosopher, the program must run until he dies because he only has one fork*/
	/*Timer for last meal starts as soon as the philo starts to eat*/
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	if (argc > 6 || argc < 5)
	{
		error_message(ARG_NUM_ERROR);
		return (1);
	}
	data = malloc(sizeof(t_data));
	philo = malloc(sizeof(t_philo));
	//should I add * data->num_philo or not? because I am just allocating space for the pointer now so I think not.
	if (error_message(init_data(argc, argv, data)) != 0)
	{
		free(data);
		free(philo);
		return (1);
	}
	if (error_message(init_philos(philo, data)) != 0)
	{
		free_all(philo, data);
		destroy_all_mutex(philo, data);
		return (1);
	}
	free_all(philo, data);
	destroy_all_mutex(philo, data);
	return (0);
}
