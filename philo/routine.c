/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:52:56 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/06 17:30:19 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	check_game_status(t_vars *vars)
{
	int	status;
	pthread_mutex_lock(&vars->game_mutex);
	if (vars->game_end == 0)
		status = 0;
	else
		status = 1;
	pthread_mutex_unlock(&vars->game_mutex);
	return (status);
}

int	check_death(t_philo *philo)
{
	int	time;

	time = calc_time(philo->vars);
	if (time - philo->eat_time >= philo->vars->time_to_die)
	{
		pthread_mutex_lock(&philo->vars->game_mutex);
		printf("%d %d died\n", calc_time(philo->vars), philo->philo);
		philo->vars->game_end = 1;
		pthread_mutex_unlock(&philo->vars->game_mutex);
		return (1);
	}
	return (0);
}

void	wait_time(t_philo *philo, int time, int len)
{
	time += len;
	while (time > calc_time(philo->vars))
	{
		if (check_death(philo))
			return ;
		usleep(500);
	}
}

void	start_eating(t_philo *philo)
{
	int	time;

	while (1)
	{
		if(check_game_status(philo->vars))
			return ;
		if (check_death(philo))
			return ;
		if (!grab_fork(philo, 1))
		{
			printf("%d %d has taken a fork\n", calc_time(philo->vars), philo->philo);
			if (!grab_fork(philo, 2))
			{
				printf("%d %d has taken a fork\n", calc_time(philo->vars), philo->philo);
				if(check_game_status(philo->vars))
					return ;
				time = calc_time(philo->vars);
				printf("%d %d is eating\n", time, philo->philo);
				philo->eat_time = time;
				philo->eat_times++;
				wait_time(philo, time, philo->vars->time_to_eat);
				free_fork(philo, 2);
				return ;
			}
			else
				free_fork(philo, 1);
		}
		wait_time(philo, calc_time(philo->vars), (philo->eat_time - calc_time(philo->vars) - philo->vars->time_to_die) / 2);
	}
}

void	start_sleeping(t_philo *philo)
{
	if (check_game_status(philo->vars))
		return ;
	printf("%d %d is sleeping\n", calc_time(philo->vars), philo->philo);
	wait_time(philo, calc_time(philo->vars), philo->vars->time_to_sleep);
}

void	*routine(void *arg)
{
	t_vars	*vars;
	t_philo	*philo;

	philo = (t_philo *)arg;
	vars = philo->vars;
	pthread_mutex_lock(&vars->game_mutex);
	pthread_mutex_unlock(&vars->game_mutex);
	while (1)
	{
		if(check_game_status(vars))
			return (NULL);
		printf("%d %d is thinking\n", calc_time(vars), philo->philo);
		start_eating(philo);
		start_sleeping(philo);
	}
}
