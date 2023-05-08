/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:36:21 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/08 16:06:31 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philos(t_philo *philo, pthread_mutex_t lock)
{
	int	i;

	i = 0;
	while (philo->data->num_philos > i)
	{
		if (pthread_create(&philo[i].th, NULL, &life_of_a_philo,
				(void *)&lock) != 0)
			exit_error("Thread error\n");
		philo[i].id = i + 1;
		pthread_mutex_init(&philo[i].right_fork, NULL);
		if (i == 0)
			philo[i].left_fork = &philo[philo->data->num_philos - 1].right_fork;
		else
			philo[i].left_fork = &philo[i - 1].right_fork;
		printf("Philo[%i] right: %p\n", i, &philo[i].right_fork);
		printf("Philo[%i] left: %p\n", i, &philo[i + 1].left_fork);
		i++;
	}
}

void	init_data(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	if (data->num_philos > 200)
		exit(1);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		exit(1);
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	data->beginning = get_time();
}
