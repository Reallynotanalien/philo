/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:20:04 by kafortin          #+#    #+#             */
/*   Updated: 2023/04/24 16:00:25 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Calculates the length of a string.*/
size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	if (str == NULL)
		return (0);
	while (str[a] != '\0')
		a++;
	return (a);
}

/*Converts the string argument "str" to an integer.*/
long	ft_atoi(const char *str)
{
	int		a;
	int		sign;
	long	res;

	a = 0;
	sign = 1;
	res = 0;
	while ((str[a] >= 9 && str[a] <= 13) || str[a] == 32)
		a++;
	if (str[a] == '+' || str[a] == '-')
	{
		if (str[a] == '-')
			sign *= -1;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		res *= 10;
		res += str[a] - '0';
		a++;
	}
	return (res * sign);
}

void	init_philos(int num_philos)
{
	while (num_philos > 0)
	{
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
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc > 6 || argc < 5)
		exit_error(ARG_NUM_ERROR);
	memset(&data, 0, sizeof(t_data));
	init_data(argc, argv, &data);
}
