/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:36:21 by kafortin          #+#    #+#             */
/*   Updated: 2023/04/27 18:03:17 by kafortin         ###   ########.fr       */
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
	data->beginning = get_time();
}
