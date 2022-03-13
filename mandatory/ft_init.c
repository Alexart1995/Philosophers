/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snuts <snuts@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:29:48 by snuts             #+#    #+#             */
/*   Updated: 2021/12/28 23:07:02 by snuts            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parse(char **argv, t_all_philos *g_phi)
{
	g_phi->params.n_o_p = ft_atoi(argv[1]);
	g_phi->params.time_to_die = ft_atoi(argv[2]);
	g_phi->params.time_to_eat = ft_atoi(argv[3]);
	g_phi->params.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		g_phi->params.n_o_p_m = ft_atoi(argv[5]);
	else
		g_phi->params.n_o_p_m = -1;
	g_phi->params.start_time = timestamp();
	g_phi->params.died = 0;
	g_phi->params.all_ate = 0;
	g_phi->philo = malloc (sizeof (t_philo) * g_phi->params.n_o_p);
	if (g_phi->philo == NULL)
		return (1);
	g_phi->forks = malloc (sizeof (t_fork) * g_phi->params.n_o_p);
	if (g_phi->forks == NULL)
		return (1);
	return (0);
}

int	ft_init_params(char **argv, t_all_philos *g_phi)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (ft_parse(argv, g_phi) == 1)
		return (1);
	while (i < g_phi->params.n_o_p)
	{
		g_phi->philo[i].ind = i;
		g_phi->philo[i].pos = j;
		g_phi->philo[i].meal_time = 0;
		g_phi->philo[i].eat_count = 0;
		g_phi->forks[i].id_fork = j;
		if (pthread_mutex_init(&g_phi->forks[i].fork_mutex, NULL) != 0)
			return (1);
		i++;
		j++;
	}
	return (0);
}

int	ft_pthread_create(t_all_philos *g_phi)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i < g_phi->params.n_o_p)
	{
		if (pthread_create(&g_phi->philo[i].t, NULL,
				f1, (void *)(intptr_t) i) != 0)
			return (1);
		i = i + 2;
		j = j + 2;
	}
	usleep (100);
	i = 1;
	j = 2;
	while (i < g_phi->params.n_o_p)
	{
		if (pthread_create(&g_phi->philo[i].t, NULL,
				f1, (void *)(intptr_t) i) != 0)
			return (1);
		i = i + 2;
		j = j + 2;
	}
	return (0);
}

void	ft_usleep(long long time_to_wait)
{
	long long	time;

	time = timestamp();
	while (timestamp() < time + (long long) time_to_wait)
		usleep(300);
}
