/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:23:12 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/16 21:15:59 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo	t_philo;

typedef struct s_vars
{
	t_philo	*philos;
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		times_to_eat;
	int		time_to_sleep;
	int		eaten_enough;
	size_t	start_time;
	int		game_end;
	sem_t	*game_sem;
	sem_t	*forks_sem;
}	t_vars;

typedef struct s_philo
{
	int		philo;
	size_t	eat_time;
	int		eat_times;
	int		pid;
	t_vars	*vars;
}	t_philo;

void	init_vars(t_vars *vars, char **argv);
int		check_and_atoi(char *nb);
void	*p_calloc(size_t count, size_t size);
size_t	calc_time(t_vars *vars);
void	*routine(void *philo);
void	wait_time(t_philo *philo, int len);
int		start_sim(t_vars *vars);
int		print_state(t_philo *philo, const char *msg);
int		eat(t_philo *philo);

#endif
