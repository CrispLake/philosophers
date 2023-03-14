/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:08:31 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/14 16:41:00 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_vars *vars)
{
	t_fork	*forks;
	int		i;

	i = 0;
	vars->forks = p_calloc(sizeof(t_fork), vars->philo_count);
	if (!vars->forks)
		return (-1);
	forks = vars->forks;
	while (i < vars->philo_count)
	{
		if (pthread_mutex_init(&(forks[i]), NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	create_philo_mutexes(t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->philo_count)
	{
		if (pthread_mutex_init(&(vars->philos[i].philo_mutex), NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	create_philos(t_vars *vars)
{
	t_philo	*philos;
	int		i;

	vars->philos = p_calloc(sizeof(t_philo), vars->philo_count);
	if (!vars->philos)
		return (-1);
	philos = vars->philos;
	i = 0;
	while (i < vars->philo_count)
	{
		philos[i].philo = i + 1;
		philos[i].vars = vars;
		philos[i].right = &((vars->forks)[i]);
		if (i == 0)
			philos[i].left = &((vars->forks)[vars->philo_count - 1]);
		else
			philos[i].left = &((vars->forks)[i - 1]);
		i++;
	}
	return (create_philo_mutexes(vars));
}

int	create_threads(t_vars *vars)
{
	t_philo	*philos;
	int		i;

	i = 0;
	while (i < vars->philo_count)
	{
		philos = vars->philos;
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	start_sim(t_vars *vars)
{
	if (pthread_mutex_init(&(vars->game_mutex), NULL))
		return (-1);
	if (create_forks(vars))
		return (-1);
	if (create_philos(vars))
		return (-1);
	if (mutex_lock_error(&(vars->game_mutex), 1))
		return (-1);
	if (create_threads(vars))
		return (-1);
	calc_time(vars);
	if (mutex_lock_error(&(vars->game_mutex), 2))
		return (-1);
	return (0);
}
