/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:23:12 by emajuri           #+#    #+#             */
/*   Updated: 2023/02/28 14:52:18 by emajuri          ###   ########.fr       */
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

typedef struct s_fork
{
	int				fork_taken;
	pthread_mutex_t	fork_mutex;
} t_fork;

typedef struct s_philo t_philo;

typedef struct s_vars
{
	t_fork			*forks;
	t_philo			*philos;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	int				eaten_enough;
	int				start_time;
	int				game_end;
	pthread_mutex_t	game_mutex;
	pthread_mutex_t	print_mutex;
} t_vars;

typedef struct s_philo
{
	int				philo;
	int				eat_time;
	pthread_t		thread;
	struct s_fork	*right;
	struct s_fork	*left;
	t_vars			*vars;
} t_philo;

void	init_vars(t_vars *vars, char **argv);
int		check_and_atoi(char *nb);
void	*p_calloc(size_t count, size_t size);
int		calc_time(t_vars *vars);

#endif
