/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:20:04 by kafortin          #+#    #+#             */
/*   Updated: 2023/04/24 18:26:35 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*life_of_a_philo()
{
	printf("I think,\n");
	sleep(1);
	printf("I eat,\n");
	sleep(1);
	printf("I sleep.\n");
	return (NULL);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (data->num_philos > i++)
	{
		// if ((pthread_mutex_init(&data->fork[i], NULL) == -1))
		// 	exit_error(FORK_INIT_ERROR);
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
	// data->fork = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	// if (!data->fork)
	// 	exit_error(FORK_CREATION_ERROR);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	t1;
	pthread_t	t2;

	if (argc > 6 || argc < 5)
		exit_error(ARG_NUM_ERROR);
	memset(&data, 0, sizeof(t_data));
	init_data(argc, argv, &data);
	init_philos(&data);
	printf("I'm about to create the threads!\n");
	if (pthread_create(&t1, NULL, &life_of_a_philo, NULL) != 0)
		exit_error("Thread error\n");
	if (pthread_create(&t2, NULL, &life_of_a_philo, NULL) != 0)
		exit_error("Thread error\n");
	if (pthread_join(t1, NULL) != 0)
		exit_error("Thread join error\n");
	if (pthread_join(t2, NULL) != 0)
		exit_error("Thread join error\n");
}
