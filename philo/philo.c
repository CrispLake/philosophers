/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:54 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/06 16:43:03 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	create_forks(t_vars *vars)
{
	t_fork	*forks;
	int	i;

	i = 0;
	vars->forks = p_calloc(sizeof(t_fork), vars->philo_count);
	if (!vars->forks)
		return (-1);
	forks = vars->forks;
	while (i < vars->philo_count)
	{
		if (pthread_mutex_init(&(forks[i].fork_mutex), NULL))
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
	return (0);
}

int	create_threads(t_vars *vars)
{
	t_philo	*philos;
	int		i;

	i = 0;
	while (i < vars->philo_count)
	{
		philos = vars->philos;
		if (pthread_create(&(philos[i].thread), NULL, &routine, &philos[i]))
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
	pthread_mutex_lock(&(vars->game_mutex));
	if (create_threads(vars))
		return (-1);
	calc_time(vars);
	pthread_mutex_unlock(&(vars->game_mutex));
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 5 && argc != 6)
	{
		printf("Incorrect argument count\n");
		return (0);
	}
	memset(&vars, 0, sizeof(t_vars));
	init_vars(&vars, argv + 1);
	if (vars.philo_count == -1)
		return (-1);
	if (start_sim(&vars))
		return (-1);
	while (1)
	{
		if (vars.eaten_enough == vars.philo_count)
		{
			pthread_mutex_lock(&vars.game_mutex);
			vars.game_end = 1;
			pthread_mutex_unlock(&vars.game_mutex);
		}
	}
	return (0);
}
