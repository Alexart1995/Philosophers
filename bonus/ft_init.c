/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snuts <snuts@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:29:48 by snuts             #+#    #+#             */
/*   Updated: 2021/12/29 20:39:51 by snuts            ###   ########.fr       */
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
		i++;
		j++;
	}
	sem_unlink("/philo_forks");
	g_phi->forks = sem_open("/philo_forks",
			O_CREAT, S_IRWXU, g_phi->params.n_o_p);
	if (g_phi->forks <= 0)
		return (1);
	return (0);
}

void	ft_fork_create(t_all_philos *g_phi)
{
	int	i;

	i = 0;
	g_phi->params.start_time = timestamp();
	while (i < g_phi->params.n_o_p)
	{
		g_phi->philo[i].proc_id = fork();
		if (g_phi->philo[i].proc_id < 0)
			break ;
		if (g_phi->philo[i].proc_id == 0)
			p_process(i);
		i = i + 2;
	}
	usleep(100);
	i = 1;
	while (i < g_phi->params.n_o_p)
	{
		g_phi->philo[i].proc_id = fork();
		if (g_phi->philo[i].proc_id < 0)
			break ;
		if (g_phi->philo[i].proc_id == 0)
			p_process(i);
		i = i + 2;
	}
}

void	ft_usleep(long long time_to_wait)
{
	long long	time;

	time = timestamp();
	while (timestamp() < time + (long long) time_to_wait)
		usleep(100);
}

void	ft_philo_finish_eat(t_all_philos *g_phi, int i)
{
	printf("%lld %d is sleeping\n", timestamp()
		- g_phi->params.start_time, g_phi->philo[i].pos);
	if (i == 0)
	{
		sem_post(g_phi->forks);
		sem_post(g_phi->forks);
	}
	else
	{
		sem_post(g_phi->forks);
		sem_post(g_phi->forks);
	}
}
