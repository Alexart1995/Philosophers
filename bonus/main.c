/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snuts <snuts@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:53:37 by snuts             #+#    #+#             */
/*   Updated: 2021/12/29 20:57:50 by snuts            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_all_philos	g_phi;

void	ft_philo_start_eat(t_all_philos *g_phi, int i)
{
	if (i == 0)
	{
		sem_wait(g_phi->forks);
		printf("%lld %d has taken a fork\n", timestamp()
			- g_phi->params.start_time, g_phi->philo[i].pos);
		sem_wait(g_phi->forks);
		printf("%lld %d has taken a fork\n", timestamp()
			- g_phi->params.start_time, g_phi->philo[i].pos);
	}
	else
	{
		sem_wait(g_phi->forks);
		printf("%lld %d has taken a fork\n", timestamp()
			- g_phi->params.start_time, g_phi->philo[i].pos);
		sem_wait(g_phi->forks);
		printf("%lld %d has taken a fork\n", timestamp()
			- g_phi->params.start_time, g_phi->philo[i].pos);
	}
	printf("%lld %d is eating\n", timestamp()
		- g_phi->params.start_time, g_phi->philo[i].pos);
	ft_usleep(g_phi->params.time_to_eat);
}

void	*fork_death_check(void *a)
{
	int	i;

	i = (intptr_t) a;
	while (42)
	{
		if (((timestamp() - g_phi.philo[i].meal_time) > g_phi.params.time_to_die
				&& g_phi.philo[i].meal_time != 0) || ((timestamp()
					- g_phi.params.start_time > g_phi.params.time_to_die)
				&& g_phi.philo[i].meal_time == 0))
		{
			g_phi.params.died = 1;
			printf("%lld %d is died\n", timestamp()
				- g_phi.params.start_time, g_phi.philo[i].pos);
			pthread_detach(g_phi.philo[i].t);
			exit (1);
		}
		if (g_phi.params.died == 1)
			exit (1);
		if (g_phi.params.all_ate == g_phi.params.n_o_p * g_phi.params.n_o_p_m)
			exit (1);
	}	
	return (NULL);
}

void	p_process(int i)
{
	if (pthread_create(&g_phi.philo[i].t, NULL,
			fork_death_check, (void *)(intptr_t) i) != 0)
		exit (1);
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
	pthread_detach(g_phi.philo[i].t);
	if (g_phi.params.died == 1 || g_phi.params.all_ate
		== g_phi.params.n_o_p * g_phi.params.n_o_p_m)
		exit (1);
	exit (0);
}

void	*f1(void *a)
{
	int	i;

	i = (intptr_t) a;
	while (g_phi.params.died != 1 && (g_phi.philo->eat_count
			< g_phi.params.n_o_p_m))
	{
		ft_philo_start_eat(&g_phi, i);
		ft_philo_finish_eat(&g_phi, i);
		g_phi.philo->eat_count++;
		g_phi.params.all_ate++;
		g_phi.philo->meal_time = timestamp();
		ft_usleep(g_phi.params.time_to_sleep);
		printf("%lld %d is thinking\n", timestamp()
			- g_phi.params.start_time, g_phi.philo->pos);
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
	ft_fork_create(&g_phi);
	exit_launcher(&g_phi);
	return (0);
}
