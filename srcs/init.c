/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:36:21 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/08 17:46:08 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->data->num_philos > i)
	{
		philo[i].id = i + 1;
		if (pthread_create(&philo[i].th, NULL, &life_of_a_philo, &philo[i]) != 0)
			exit_error("Thread error\n");
		printf("Philo[%i]\n", philo[i].id);
		philo[i].right_fork = &philo->data->fork[i];
		if (i == 0)
			philo[i].left_fork = &philo->data->fork[philo->data->num_philos - 1];
		else
			philo[i].left_fork = &philo->data->fork[i - 1];
		i++;
	}
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	while (data->num_philos > i)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) == -1)
			exit_error("ERROR CREATING FORKS\n");
		i++;
	}
}

void	init_data(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	if (data->num_philos > 200)
		exit_error("There is too many philos!!!\n");
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		exit_error("The time should be bigger than 60ms\n");
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	data->beginning = get_time();
}
