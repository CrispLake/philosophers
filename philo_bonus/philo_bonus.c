/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:54:15 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/16 18:03:24 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_death(t_philo *philo)
{
	size_t	time;

	// if (mutex_lock_error(&philo->vars->game_mutex, 1))
	// 	return (-1);
	time = calc_time(philo->vars);
	if (time - philo->eat_time >= (size_t)philo->vars->time_to_die)
	{
		printf("%lu %d died\n", time, philo->philo);
		philo->vars->game_end = 1;
		// if (mutex_lock_error(&philo->vars->game_mutex, 2))
		// 	return (-1);
		return (1);
	}
	// if (mutex_lock_error(&philo->vars->game_mutex, 2))
	// 	return (-1);
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
			// if (mutex_lock_error(&vars->philos[i].philo_mutex, 1))
			// 	return (-1);
			if (vars->eaten_enough == vars->philo_count || 
				check_death(&vars->philos[i]))
			{
				end = 1;
				break ;
			}
			// if (mutex_lock_error(&vars->philos[i].philo_mutex, 2))
			// 	return (-1);
			i++;
		}
		wait_time(vars->philos, 5);
	}
	// if (mutex_lock_error(&vars->philos[i].philo_mutex, 2))
	// 	return (-1);
	return (0);
}

int	destroy_sems(t_vars *vars)
{
	sem_close(vars->game_sem);
	sem_close(vars->forks_sem);
	sem_unlink("game_sem");
	sem_unlink("forks_sem");
	return (0);
}

int	kill_children(t_vars *vars)
{
	int	i;
	
	i = 0;
	while (i < vars->philo_count)
	{
		kill(vars->philos[i].pid, SIGKILL);
		i++;
	}
	destroy_sems(vars);
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
		return (kill_children(&vars));
	if (monitor(&vars))
		return (kill_children(&vars));
	return (kill_children(&vars));
}
