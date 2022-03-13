/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snuts <snuts@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:19:10 by snuts             #+#    #+#             */
/*   Updated: 2021/12/27 20:59:17 by snuts            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_died1(t_all_philos *g_phi, int j)
{
	int	i;

	i = 0;
	printf("%lld %d is died\n", timestamp()
		- g_phi->params.start_time, g_phi->philo[j].pos);
	g_phi->params.died = 1;
	while (i < g_phi->params.n_o_p)
	{
		pthread_detach(g_phi->philo[i].t);
		i++;
	}
	i = 0;
	while (i < g_phi->params.n_o_p)
	{
		pthread_mutex_destroy(&g_phi->forks[i].fork_mutex);
		i++;
	}
}

void	ft_died2(t_all_philos *g_phi, int j)
{
	int	i;

	i = 0;
	printf("%lld %d is died\n", timestamp()
		- g_phi->params.start_time, g_phi->philo[j].pos);
	g_phi->params.died = 1;
	while (i < g_phi->params.n_o_p)
	{
		pthread_detach(g_phi->philo[i].t);
		i++;
	}
	i = 0;
	while (i < g_phi->params.n_o_p)
	{
		pthread_mutex_destroy(&g_phi->forks[i].fork_mutex);
		i++;
	}
}

void	ft_all_ate(t_all_philos *g_phi)
{
	int	j;

	j = 0;
	while (j < g_phi->params.n_o_p)
	{
		pthread_detach(g_phi->philo[j].t);
		j++;
	}
	j = 0;
	while (j < g_phi->params.n_o_p)
	{
		pthread_mutex_destroy(&g_phi->forks[j].fork_mutex);
		j++;
	}
}

void	ft_checked_died(t_all_philos *g_phi)
{
	int	j;

	j = 0;
	while (j < g_phi->params.n_o_p)
	{
		if ((timestamp() - g_phi->params.start_time
				> g_phi->params.time_to_die) && g_phi->philo[j].meal_time == 0)
		{
			ft_died1(g_phi, j);
			break ;
		}
		else if ((timestamp() - g_phi->philo[j].meal_time)
			> g_phi->params.time_to_die && g_phi->philo[j].meal_time != 0)
		{
			ft_died2(g_phi, j);
			break ;
		}
		else if (g_phi->params.all_ate
			== g_phi->params.n_o_p * g_phi->params.n_o_p_m)
		{
			ft_all_ate(g_phi);
			break ;
		}
		j++;
	}	
}
