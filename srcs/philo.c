/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:20:04 by kafortin          #+#    #+#             */
/*   Updated: 2023/04/27 18:16:32 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

long int	sleeping(t_data *data)
{
	printf("%ld %i is sleeping\n");
	usleep(data->time_to_sleep * 1000);
}

void	*life_of_a_philo(void *lock)
{
	pthread_mutex_lock(lock);
	printf("I think,\n");
	usleep(10423);
	printf("I eat,\n");
	usleep(15440);
	printf("I sleep.\n");
	pthread_mutex_unlock(lock);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	lock;
	int				i;
	long int		now;
	long int		beginning;

	beginning = get_time();
	if (argc > 6 || argc < 5)
		exit_error(ARG_NUM_ERROR);
	memset(&data, 0, sizeof(t_data));
	philo = malloc(sizeof(t_philo) * 10);
	init_data(argc, argv, &data);
	philo->data = &data;
	pthread_mutex_init(&lock, NULL);
	init_philos(philo, lock);
	i = 0;
	while (philo->data->num_philos > i)
	{
		if (pthread_join(philo[i].th, NULL) != 0)
			exit_error("Thread join error\n");
		now = get_time();
		now -= beginning;
		printf("time: %ld\nphilo[%i]\n", now, philo[i].id);
		i++;
	}
	pthread_mutex_destroy(&lock);
}
