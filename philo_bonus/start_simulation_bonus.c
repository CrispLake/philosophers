/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:08:31 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/28 16:29:17 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		i++;
	}
	return (0);
}

int	create_semaphores(t_vars *vars)
{
	vars->game_sem = sem_open("game_sem", O_CREAT | O_EXCL, 0644, 0);
	sem_unlink("game_sem");
	if (vars->game_sem == SEM_FAILED)
	{
		printf("Error creating game_sem\n");
		return (-1);
	}
	vars->forks_sem = sem_open("forks_sem", O_CREAT | O_EXCL, 0644, vars->philo_count);
	sem_unlink("forks_sem");
	if (vars->forks_sem == SEM_FAILED)
	{
		printf("Error creating forks_sem\n");
		return (-1);
	}
	vars->eat_sem = sem_open("eat_sem", O_CREAT | O_EXCL, 0644, 0);
	sem_unlink("eat_sem");
	if (vars->forks_sem == SEM_FAILED)
	{
		printf("Error creating eat_sem\n");
		return (-1);
	}
	return (0);
}

int	create_processes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philo_count)
	{
		vars->philos[i].pid = fork();
		if (vars->philos[i].pid == -1)
			return (-1);
		if (!vars->philos[i].pid)
			child(&vars->philos[i]);
		i++;
	}
	return (0);
}

int	start_sim(t_vars *vars)
{
	if (create_philos(vars))
		return (-1);
	if (create_semaphores(vars))
		return (-1);
	if (create_processes(vars))
		return (-1);
	wait_time(&vars->philos[0], 100);
	calc_time(vars);
	sem_post(vars->game_sem);
	return (0);
}
