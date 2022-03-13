/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snuts <snuts@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:54:08 by snuts             #+#    #+#             */
/*   Updated: 2021/12/27 22:46:44 by snuts            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(void)
{
	write(1, "Error value\n", 6);
	exit(0);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_checker(int argc, char **str)
{
	int	i;
	int	j;

	j = 1;
	while (j < argc)
	{
		i = 0;
		while (str[j][i] != '\0')
		{
			if ((str[j][i] < '0' || str[j][i] > '9')
				&& str[j][i] != '-' && str[j][i] != '+')
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int						i;
	long int				num;
	int						min;

	min = 1;
	num = 0;
	i = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		&& str[i] != '\0')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			min = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0' && str[i] != '\0')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	if (min * num < -2147483648 || min * num > 2147483647)
		ft_error();
	return (min * num);
}
