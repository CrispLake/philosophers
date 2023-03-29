/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:06:36 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/29 14:40:19 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_death(t_philo *philo)
{
	size_t	time;

	time = calc_time(philo->vars);
	if (time - philo->eat_time >= (size_t)philo->vars->time_to_die)
	{
		sem_wait(philo->vars->game_sem);
		printf("%lu %d died\n", calc_time(philo->vars), philo->philo);
		return (1);
	}
	return (0);
}

int	*monitoring(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->vars->monitor_sem);
		if (check_death(philo))
			return (NULL);
		sem_post(philo->vars->monitor_sem);
		wait_time(philo, 5);
	}
	return (NULL);
}

int	create_monitor_sem(int philo, t_vars *vars)
{
	char	*id;
	char	*monitor;

	id = p_itoa(philo);
	monitor = p_strjoin("monitor_sem", id);
	free(id);
	vars->monitor_sem = sem_open(monitor, O_CREAT | O_EXCL, 0644, 0);
	sem_unlink(monitor);
	if (vars->monitor_sem == SEM_FAILED)
	{
		printf("Error creating %s\n", monitor);
		free(monitor);
		return (-1);
	}
	free(monitor);
	return (0);
}

void	child(t_philo *philo)
{
	pthread_t	thread;

	if (create_monitor_sem(philo->philo, philo->vars))
		exit(-1);
	if (pthread_create(&thread, NULL, routine, philo))
		exit(-1);
	monitoring(philo);
	sem_close(philo->vars->monitor_sem);
	exit(philo->philo);
}
