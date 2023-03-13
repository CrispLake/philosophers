/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:23:12 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/13 18:04:33 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>

typedef long long t_microsec;

typedef pthread_mutex_t	t_fork;

typedef struct s_philo	t_philo;

typedef struct s_vars
{
	t_fork			*forks;
	t_philo			*philos;
	int				philo_count;
	t_microsec		time_to_die;
	t_microsec		time_to_eat;
	int				times_to_eat;
	t_microsec		time_to_sleep;
	int				eaten_enough;
	t_microsec		start_time;
	int				game_end;
	pthread_mutex_t	game_mutex;
}	t_vars;

typedef struct s_philo
{
	pthread_mutex_t	philo_mutex;
	int			philo;
	t_microsec	eat_time;
	int			eat_times;
	pthread_t	thread;
	t_fork		*right;
	t_fork		*left;
	t_vars		*vars;
}	t_philo;

void		init_vars(t_vars *vars, char **argv);
int			check_and_atoi(char *nb);
void		*p_calloc(size_t count, size_t size);
t_microsec	calc_time(t_vars *vars);
void		*routine(void *philo);
int			mutex_lock_error(pthread_mutex_t *mutex, int lock);
void		wait_time(t_philo *philo, t_microsec len);
int			start_sim(t_vars *vars);
int			function_in_mutex(void f(t_philo *philo, t_microsec time),
				t_philo *philo, const char *msg);
int			eat(t_philo *philo);

#endif
