/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:44:01 by kafortin          #+#    #+#             */
/*   Updated: 2023/04/26 17:37:38 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Writes ERROR - followed by the error message sent as an argument to the 
terminal before exiting the program with errno.*/
void	exit_error(char *error)
{
	write(2, "ERROR - ", 8);
	write(2, error, ft_strlen(error));
	exit(errno);
}

/*Writes ERROR - followed by the error message sent as an argument to the 
terminal before exiting the program with errno.*/
// void	thread_exit_error(char *error)
// {
// 	write(2, "ERROR - ", 8);
// 	write(2, error, ft_strlen(error));
// 	pthread_exit(errno);
// }
