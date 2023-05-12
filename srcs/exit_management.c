/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:44:01 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/12 16:24:42 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Writes ERROR - followed by the error message sent as an argument to the 
terminal before exiting the program with errno.*/
int	error_message(char *error)
{
	if (error == NULL)
		return (1);
	write(2, "ERROR - ", 8);
	write(2, error, ft_strlen(error));
	return (0);
}

void	free_all(t_philo *philo, t_data *data)
{
	free(data->fork);
	free(philo);
	free(data);
}

void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (data->num_philos > i)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
}

void	destroy_all_mutex(t_philo *philo, t_data *data)
{
	destroy_forks(data);
}

/*Writes ERROR - followed by the error message sent as an argument to the 
terminal before exiting the program with errno.*/
// void	thread_error_message(char *error)
// {
// 	write(2, "ERROR - ", 8);
// 	write(2, error, ft_strlen(error));
// 	pthread_exit(errno);
// }
