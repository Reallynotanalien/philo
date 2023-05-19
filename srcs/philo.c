/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:20:04 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/19 18:11:53 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
	{
		error_message(ARG_NUM_ERROR);
		return (1);
	}
	if (ft_isdigit(argc, argv) != 0)
		return (1);
	return (0);
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
	philo = malloc(sizeof(t_philo));
	//should I add * data->num_philo or not? because I am just allocating
	//space for the pointer now so I think not.
	if (init_philos(philo, data) != 0)
		return (1);
	destroy_and_free_data(data);
}
