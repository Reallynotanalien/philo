/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:20:04 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/06 16:56:09 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Parses the args and if everything is good, mallocs and inits the data and the
associated mutexes. Then, mallocs and inits the philosophers and starts their
threads. After that, the undertaker will check if one of the philo died or if
they are all full, and he will do that until one of those things happens.
The main function then wait for all the threads to finish and destroys and free
all the mallocked data and mutexes.
If there is any error occuring, the program returns 1.*/
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
	return (0);
}
