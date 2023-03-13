/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:54 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/13 19:04:36 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	t_microsec	time;

	time = calc_time(philo->vars);
	if (time - philo->eat_time >= philo->vars->time_to_die)
	{
		if (mutex_lock_error(&philo->vars->game_mutex, 1))
			return (-1);
		printf("eat times: %d\neat time: %llu\nlate: %llu\n", philo->eat_times, philo->eat_time, (time - (philo->eat_time + philo->vars->time_to_die)) / 1000);
		printf("%llu %d died\n", (philo->eat_time + philo->vars->time_to_die) / 1000, philo->philo);
		return (1);
	}
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
			if (check_death(&vars->philos[i]) || 
				vars->eaten_enough == vars->philo_count)
			{
				vars->game_end = 1;
				end = 1;
				if (mutex_lock_error(&vars->game_mutex, 2))
					return (-1);
				break ;
			}
			if (mutex_lock_error(&vars->philos[i].philo_mutex, 2))
				return (-1);
			i++;
		}
		usleep(100);
	}
	if (mutex_lock_error(&vars->philos[i].philo_mutex, 2))
		return (-1);
	return (0);
}

int	wait_all_threads(t_vars *vars)
{
	int	i;
	int	ret;

	i = 0;
	ret = pthread_join(vars->philos[i].thread, NULL);
	while (!ret && i < vars->philo_count - 1)
	{
		i++;
		ret = pthread_join(vars->philos[i].thread, NULL);
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
		pthread_mutex_destroy(&vars->forks[i++]);
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
