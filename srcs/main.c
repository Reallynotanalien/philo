/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:20:04 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/05 15:42:22 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	undertaker(philo, data);
	wait_for_philos(philo);
	destroy_and_free_data(data);
	free(philo);
}
