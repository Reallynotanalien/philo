/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:19:55 by kafortin          #+#    #+#             */
/*   Updated: 2023/04/24 16:00:40 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*INCLUDES*/
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/*ERROR MESSAGES*/
# define ARG_NUM_ERROR "The arguments sent \n"

/*STRUCTS*/
typedef struct philo
{
	void	*data;
}			t_philo;

typedef struct data
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_meals;
}			t_data;

size_t	ft_strlen(const char *str);

/*exit_management*/
void	exit_error(char *error);

#endif