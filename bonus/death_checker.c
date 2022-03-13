/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snuts <snuts@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:19:10 by snuts             #+#    #+#             */
/*   Updated: 2021/12/29 20:01:45 by snuts            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_died1(t_all_philos *g_phi, int j)
{
	int	i;

	i = 0;
	j = 0;
	g_phi->params.died = 1;
	while (i < g_phi->params.n_o_p)
	{
		kill(g_phi->philo[i].proc_id, 15);
		i++;
	}
	sem_close(g_phi->forks);
	sem_unlink("/philo_forks");
}

void	ft_died2(t_all_philos *g_phi, int j)
{
	int	i;

	i = 0;
	j = 0;
	g_phi->params.died = 1;
	while (j < g_phi->params.n_o_p)
	{
		kill(g_phi->philo[j].proc_id, 9);
		j++;
	}
	sem_close(g_phi->forks);
	sem_unlink("/philo_forks");
}

void	ft_all_ate(t_all_philos *g_phi)
{
	int	j;

	j = 0;
	while (j < g_phi->params.n_o_p)
	{
		kill(g_phi->philo[j].proc_id, 15);
		j++;
	}
	sem_close(g_phi->forks);
	sem_unlink("/philo_forks");
}

void	exit_launcher(t_all_philos *g_phi)
{
	int	i;
	int	ret;

	i = 0;
	while (i < g_phi->params.n_o_p)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < g_phi->params.n_o_p)
				kill(g_phi->philo[i].proc_id, 15);
			break ;
		}
		i++;
	}
	sem_close(g_phi->forks);
}

void	ft_checked_died(t_all_philos *g_phi)
{
	int	j;

	while (21)
	{
		if (g_phi->params.died == 1)
		{
			j = 0;
			while (j < g_phi->params.n_o_p)
			{
				kill(g_phi->philo[j].proc_id, 9);
				j++;
			}
			sem_close(g_phi->forks);
			sem_unlink("/philo_forks");
			break ;
		}
	}
}
