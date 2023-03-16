/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:08:31 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/16 21:15:49 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/semaphore.h>

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
	vars->game_sem = sem_open("game_sem", O_CREAT, 0644, 0);
	if (vars->game_sem == SEM_FAILED)
	{
		printf("Error creating game_sem\n");
		return (-1);
	}
	vars->forks_sem = sem_open("forks_sem", O_CREAT, 0644, vars->philo_count);
	if (vars->forks_sem == SEM_FAILED)
	{
		sem_close(vars->game_sem);
		sem_unlink("game_sem");
		printf("Error creating forks_sem\n");
		return (-1);
	}
	return (0);
}

int	create_processes(t_vars *vars)
{
	int	i;

	i = 0;
	(void)vars;
	return (0);
}

void	child(t_philo *philo)
{
	int i = 0;
	printf("Hello\n");
	sem_open("game_sem", 0);
	sem_open("forks_sem", 0);
	sem_wait(philo->vars->game_sem);
	sem_post(philo->vars->game_sem);
	while (i < 10)
	{
		printf("philo %d: Heyyy\n", philo->philo);
		usleep(10 * 1000 * 1000);
		i++;
	}
	sem_close(philo->vars->forks_sem);
	sem_close(philo->vars->game_sem);
	printf("%d left\n", philo->philo);
	exit(0);
}

void	delete_this(t_vars *vars)
{
	int i = 0;
	int	pid;

	while (i < vars->philo_count)
	{
		pid = fork();
		printf("pid: %d\n", pid);
		if (!pid)
			child(&vars->philos[i]);
		printf("Created %d\n", i + 1);
		i++;
	}
	usleep(5 * 1000 * 1000);
	printf("Starting\n");
	sem_post(vars->game_sem);
	i = 0;
	while (i < 10)
	{
		printf("parent: %d\n", i);
		usleep(10 * 1000 * 1000);
		i++;
	}
	sem_close(vars->game_sem);
	sem_close(vars->forks_sem);
	sem_unlink("game_sem");
	sem_unlink("forks_sem");
	printf("leaving\n");
	exit (-1);
}

int	start_sim(t_vars *vars)
{
	if (create_philos(vars))
		return (-1);
	if	(create_semaphores(vars))
		return (-1);
	delete_this(vars);
	if (create_processes(vars))
		return (-1);
	// if (mutex_lock_error(&(vars->game_mutex), 1))
	// 	return (-1);
	// if (create_threads(vars))
	// 	return (-1);
	calc_time(vars);
	// if (mutex_lock_error(&(vars->game_mutex), 2))
	// 	return (-1);
	return (0);
}
