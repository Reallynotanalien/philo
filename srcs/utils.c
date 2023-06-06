/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:51:02 by kafortin          #+#    #+#             */
/*   Updated: 2023/06/06 16:42:41 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				error_message(NUMERIC_ERROR);
				return (1);
			}
			if (argv[i][j + 1] == '\0')
				break ;
			j++;
		}
		i++;
	}
	return (0);
}

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

/*Compares between two strings and returns 0 if both are equal, or 1 
if they are not.*/
int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	a;

	a = 0;
	while (((unsigned char)str1[a] != '\0' || (unsigned char)str2[a] != '\0'))
	{
		if ((unsigned char)str1[a] != (unsigned char)str2[a])
			return ((unsigned char)str1[a] - (unsigned char)str2[a]);
		a++;
	}
	return (0);
}

void	error_message(char *error)
{
	write(2, "ERROR - ", 8);
	write(2, error, ft_strlen(error));
}
