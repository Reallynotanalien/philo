/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:20:04 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/16 14:59:32 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc)
{
	if (argc > 6 || argc < 5)
	{
		error_message(ARG_NUM_ERROR);
		return (1);
	}
	//check if numerics too!!!
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	// t_philo	*philo;

	if (check_args(argc) != 0)
		return (1);
	if (init_data(argc, argv, &data) != 0 || init_mutex(&data) != 0)
		return (1);
	destroy_forks(&data);
	pthread_mutex_destroy(data.write_access);
	pthread_mutex_destroy(data.death);
	free(data.fork);
	free(data.write_access);
	free(data.death);
}
