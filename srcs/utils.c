/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:51:02 by kafortin          #+#    #+#             */
/*   Updated: 2023/05/12 15:49:27 by kafortin         ###   ########.fr       */
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
