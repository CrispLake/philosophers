/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:54 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/15 17:19:22 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	check_death(t_philo *philo)
{
	size_t	time;

	if (mutex_lock_error(&philo->vars->game_mutex, 1))
		return (-1);
	time = calc_time(philo->vars);
	if (time - philo->eat_time >= (size_t)philo->vars->time_to_die)
	{
		printf("%lu %d died\n", time, philo->philo);
		philo->vars->game_end = 1;
		if (mutex_lock_error(&philo->vars->game_mutex, 2))
			return (-1);
		return (1);
	}
	if (mutex_lock_error(&philo->vars->game_mutex, 2))
		return (-1);
	return (0);
}

int	monitor(t_vars *vars)
{
	int	i;
	int	end;

	end = 0;
	while (!end)
	{
		i = 0;
		while (i < vars->philo_count)
		{
			if (mutex_lock_error(&vars->philos[i].philo_mutex, 1))
				return (-1);
			if (vars->eaten_enough == vars->philo_count || 
				check_death(&vars->philos[i]))
			{
				end = 1;
				break ;
			}
			if (mutex_lock_error(&vars->philos[i].philo_mutex, 2))
				return (-1);
			i++;
		}
		wait_time(vars->philos, 5);
	}
	if (mutex_lock_error(&vars->philos[i].philo_mutex, 2))
		return (-1);
	return (0);
}

int	wait_all_threads(t_vars *vars)
{
	int	i;
	int	ret;
	int	*philo;

	i = 0;
	ret = 0;
	while (!ret && i < vars->philo_count)
	{
		ret = pthread_join(vars->philos[i].thread, (void *)&philo);
		i++;
	}
	if (ret)
		return (-1);
	return (0);
}

int	destroy_mutexes(t_vars *vars)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&vars->game_mutex);
	while (i < vars->philo_count)
	{
		pthread_mutex_destroy(&vars->forks[i]);
		pthread_mutex_destroy(&vars->philos[i].philo_mutex);
		i++;
	}
	free(vars->forks);
	free(vars->philos);
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
	if (vars.philo_count == -1 || vars.times_to_eat == 0)
		return (-1);
	if (start_sim(&vars))
		return (destroy_mutexes(&vars));
	if (monitor(&vars))
		return (destroy_mutexes(&vars));
	if (wait_all_threads(&vars))
		return (destroy_mutexes(&vars));
	return (destroy_mutexes(&vars));
}
