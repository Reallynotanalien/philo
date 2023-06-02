/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:20:04 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/02 18:21:28 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
		return (error_message(ARG_NUM_ERROR), 1);
	if (ft_isdigit(argc, argv) != 0)
		return (error_message(NUMERIC_ERROR), 1);
	return (0);
}

void	medical_checkup(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (check_if_someone_died(&philo[i]) == DEAD)
			return ;
		i++;
		if (i == data->num_philos)
			i = 0;
	}
}

void	wait_for_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_philos)
	{
		if (pthread_join(philo[i].th, NULL) != 0)
			return ;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	if (check_args(argc, argv) != 0)
		return (1);
	data = malloc(sizeof(t_data));
	if (init_data(argc, argv, data) != 0 || init_mutex(data) != 0)
		return (1);
	philo = malloc(sizeof(t_philo) * data->num_philos);
	if (init_philos(philo, data) != 0)
		return (1);
	medical_checkup(philo, data);
	wait_for_philos(philo);
	destroy_and_free_data(data);
	free(philo);
}
