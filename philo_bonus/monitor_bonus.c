/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:14:55 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/29 14:15:02 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/fcntl.h>

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
		wait_time(vars->philos, 5);
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

int	monitor(t_vars *vars)
{
	pthread_t	monitors[2];

	vars->monitor_sem = sem_open("monitor_sem", O_CREAT | O_EXCL, 0644, 1);
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
	sem_close(vars->monitor_sem);
	return (0);
}
