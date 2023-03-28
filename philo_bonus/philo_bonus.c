/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:54:15 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/28 16:49:23 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_sems(t_vars *vars)
{
	if (vars->game_sem)
		sem_close(vars->game_sem);
	if (vars->forks_sem)
		sem_close(vars->forks_sem);
	if (vars->eat_sem)
		sem_close(vars->eat_sem);
}

int	kill_children(t_vars *vars, int dead)
{
	int	i;

	i = 0;
	while (i < vars->philo_count)
	{
		if (vars->philos[i].philo == dead)
			i++;
		if (!vars->philos[i].pid)
			break ;
		kill(vars->philos[i].pid, SIGKILL);
		i++;
	}
	i = 0;
	while (i < vars->philo_count)
	{
		if (vars->philos[i].philo == dead)
			i++;
		if (!vars->philos[i].pid)
			break ;
		waitpid(vars->philos[i].pid, NULL, 0);
		i++;
	}
	destroy_sems(vars);
	return (0);
}

void	*end_after_death(t_vars *vars, int status)
{
	if (status == -1)
		printf("Error in child process\n");
	vars->monitor = status;
	sem_post(vars->monitor_sem);
	sem_post(vars->eat_sem);
	return (NULL);
}

void	*death(void *arg)
{
	t_vars	*vars;
	int		i;
	int		status;

	vars = (t_vars *)arg;
	status = 0;
	while (1)
	{
		i = 0;
		while (i < vars->philo_count)
		{
			sem_wait(vars->monitor_sem);
			if (vars->monitor)
				return (NULL);
			waitpid(vars->philos[i].pid, &status, WNOHANG);
			if (status != 0)
				return (end_after_death(vars, status));
			sem_post(vars->monitor_sem);
			i++;
		}
		wait_time(&vars->philos[0], 4);
	}
	return (NULL);
}

void	*eat_count(void *arg)
{
	t_vars	*vars;
	int		i;

	vars = (t_vars *)arg;
	i = 0;
	while (i < vars->philo_count)
	{
		sem_wait(vars->monitor_sem);
		if (vars->monitor)
			return (NULL);
		sem_post(vars->monitor_sem);
		sem_wait(vars->eat_sem);
		i++;
	}
	sem_wait(vars->monitor_sem);
	if (!vars->monitor)
		vars->monitor = -1;
	sem_post(vars->monitor_sem);
	return (NULL);
}

static int	monitor(t_vars *vars)
{
	pthread_t	monitors[2];

	vars->monitor_sem = sem_open("monitor_sem", O_CREAT, 0644, 1);
	sem_unlink("monitor_sem");
	if (vars->monitor_sem == SEM_FAILED)
	{
		printf("Error creating monitor_sem\n");
		return (-1);
	}
	if (pthread_create(&monitors[DEATH], NULL, death, vars))
	{
		sem_close(vars->monitor_sem);
		return (-1);
	}
	if (pthread_create(&monitors[EAT], NULL, eat_count, vars))
	{
		sem_close(vars->monitor_sem);
		return (-1);
	}
	pthread_join(monitors[DEATH], NULL);
	pthread_join(monitors[EAT], NULL);
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
		return (kill_children(&vars, 0));
	if (monitor(&vars))
		return (kill_children(&vars, vars.monitor));
	return (kill_children(&vars, vars.monitor));
}
