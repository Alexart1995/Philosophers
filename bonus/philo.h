/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snuts <snuts@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 20:39:13 by snuts             #+#    #+#             */
/*   Updated: 2021/12/29 19:37:30 by snuts            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_params {
	int				n_o_p;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_think;
	long long		time_to_sleep;
	size_t			all_ate;
	size_t			n_o_p_m;
	long long		start_time;
	pthread_mutex_t	writing;
	int				died;
}	t_params;

typedef struct s_philo {
	pid_t			proc_id;
	int				ind;
	int				pos;
	char			name;
	int				lfork;
	int				rfork;
	pthread_t		t;
	t_params		*params;
	size_t			eat_count;
	int				is_started;
	long long		meal_time;
	pthread_mutex_t	meal_lock;

}	t_philo;

typedef struct s_fork {
	int				id_fork;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_all_philos
{
	t_params	params;
	t_philo		*philo;
	sem_t		*forks;
}		t_all_philos;

int			ft_atoi(char *str);
int			ft_checker(int argc, char **str);
void		ft_usleep(long long time_to_wait);
int			ft_parse(char **argv, t_all_philos *phi);
long long	timestamp(void);
int			ft_pthread_create(t_all_philos *phi);
void		*f1(void *a);
int			ft_init_params(char **argv, t_all_philos *phi);
void		ft_checked_died(t_all_philos *phi);
void		ft_philo_start_eat(t_all_philos *phi, int i);
void		ft_philo_finish_eat(t_all_philos *phi, int i);
void		ft_died1(t_all_philos *phi, int j);
void		ft_died2(t_all_philos *phi, int i);
void		ft_all_ate(t_all_philos *phi);
void		p_process(int i);
void		ft_fork_create(t_all_philos *g_phi);
void		*fork_death_check(void *a);
void		exit_launcher(t_all_philos *g_phi);
// int	ft_fork_create(t_all_philos *g_phi);
#endif