/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:20:04 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/08 17:43:36 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

// long int	sleeping(t_data *data)
// {
// 	printf("%ld %i is sleeping\n");
// 	usleep(data->time_to_sleep * 1000);
// }

void	*life_of_a_philo(void *i)
{
	t_philo	*philo;

	philo = (t_philo *)i;
	// pthread_mutex_lock(lock);
	/*I need 2 forks to eat!!*/
	printf("Philo[%i] in thread\n", philo->id);
	printf("%p\n", philo);
	printf("I eat,\n");
	usleep(10423);
	printf("I sleep.\n");
	usleep(15440);
	/*Philos think between eating and sleeping. If there is no delay between the two, he still thinks but then starts eating right away.*/
	printf("I think,\n");
	// pthread_mutex_unlock(lock);
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
	philo->data = data;
	pthread_mutex_init(&lock, NULL);
	init_forks(data);
	init_philos(philo);
	i = 0;
	while (philo->data->num_philos > i)
	{
		if (pthread_join(philo[i].th, NULL) != 0)
			exit_error("Thread join error\n");
		data->now = get_time();
		data->now -= data->beginning;
		printf("time: %ld\nphilo[%i]\n", data->now, philo[i].id);
		free(&philo[i]);
		i++;
	}
	free(philo);
	pthread_mutex_destroy(&lock);
	/*If there is only one philosopher, the program must run until he dies because he only has one fork*/
	/*Timer for last meal starts as soon as the philo starts to eat*/
}
