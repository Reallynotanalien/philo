/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:20:04 by kafortin          #+#    #+#             */
/*   Updated: 2023/04/26 18:16:36 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*life_of_a_philo(void *lock)
{
	pthread_mutex_lock(lock);
	printf("I think,\n");
	sleep(1);
	printf("I eat,\n");
	sleep(1);
	printf("I sleep.\n");
	pthread_mutex_unlock(lock);
	return (NULL);
}

void	init_philos(t_philo *philo, pthread_mutex_t lock)
{
	int	i;

	i = 0;
	while (philo->data->num_philos > i)
	{
		if (pthread_create(&philo[i].th, NULL, &life_of_a_philo,
				(void *)&lock) != 0)
			exit_error("Thread error\n");
		i++;
	}
}

void	init_data(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	lock;
	int				i;

	i = 0;
	if (argc > 6 || argc < 5)
		exit_error(ARG_NUM_ERROR);
	memset(&data, 0, sizeof(t_data));
	philo = malloc(sizeof(t_philo) * 10);
	init_data(argc, argv, &data);
	philo->data = &data;
	pthread_mutex_init(&lock, NULL);
	init_philos(philo, lock);
	i = 0;
	while (i < 10)
	{
		if (pthread_join(philo[i].th, NULL) != 0)
			exit_error("Thread join error\n");
		i++;
	}
	pthread_mutex_destroy(&lock);
}
