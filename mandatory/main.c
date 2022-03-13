/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snuts <snuts@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:53:37 by snuts             #+#    #+#             */
/*   Updated: 2021/12/28 20:23:04 by snuts            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_all_philos	g_phi;

void	ft_philo_start_eat(t_all_philos *g_phi, int i)
{
	if (i == 0)
	{
		pthread_mutex_lock(&g_phi->forks[i].fork_mutex);
		printf("%lld %d has taken a fork\n", timestamp()
			- g_phi->params.start_time, g_phi->philo[i].pos);
		pthread_mutex_lock(&g_phi->forks[g_phi->params.n_o_p
			- 1].fork_mutex);
		printf("%lld %d has taken a fork\n", timestamp()
			- g_phi->params.start_time, g_phi->philo[i].pos);
	}
	else
	{
		pthread_mutex_lock(&g_phi->forks[i].fork_mutex);
		printf("%lld %d has taken a fork\n", timestamp()
			- g_phi->params.start_time, g_phi->philo[i].pos);
		pthread_mutex_lock(&g_phi->forks[i - 1].fork_mutex);
		printf("%lld %d has taken a fork\n", timestamp()
			- g_phi->params.start_time, g_phi->philo[i].pos);
	}
	printf("%lld %d is eating\n", timestamp()
		- g_phi->params.start_time, g_phi->philo[i].pos);
	ft_usleep(g_phi->params.time_to_eat);
}

void	ft_philo_finish_eat(t_all_philos *g_phi, int i)
{
	printf("%lld %d is sleeping\n", timestamp()
		- g_phi->params.start_time, g_phi->philo[i].pos);
	if (i == 0)
	{
		pthread_mutex_unlock(&g_phi->forks[i].fork_mutex);
		pthread_mutex_unlock(&g_phi->forks[g_phi->params.n_o_p - 1].fork_mutex);
	}
	else
	{
		pthread_mutex_unlock(&g_phi->forks[i].fork_mutex);
		pthread_mutex_unlock(&g_phi->forks[i - 1].fork_mutex);
	}
}

void	*f1(void *a)
{
	int	i;

	i = (intptr_t) a;
	while (g_phi.params.died != 1 && (g_phi.philo[i].eat_count
			< g_phi.params.n_o_p_m))
	{
		ft_philo_start_eat(&g_phi, i);
		ft_philo_finish_eat(&g_phi, i);
		g_phi.philo[i].eat_count++;
		g_phi.params.all_ate++;
		g_phi.philo[i].meal_time = timestamp();
		ft_usleep(g_phi.params.time_to_sleep);
		printf("%lld %d is thinking\n", timestamp()
			- g_phi.params.start_time, g_phi.philo[i].pos);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	if ((argc != 5 && argc != 6) || ft_checker(argc, argv) == 1)
	{
		printf("Wrong args\n");
		return (1);
	}
	if (ft_init_params(argv, &g_phi) == 1)
	{
		printf("Mutex init error\n");
		return (1);
	}
	if (ft_pthread_create(&g_phi) == 1)
	{
		printf("Pthread create error\n");
		return (1);
	}
	while (1)
	{
		ft_checked_died(&g_phi);
		if (g_phi.params.died == 1 || g_phi.params.all_ate
			== g_phi.params.n_o_p * g_phi.params.n_o_p_m)
			break ;
	}
	return (0);
}
