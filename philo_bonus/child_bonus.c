/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:06:36 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/28 12:03:41 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_death(t_philo *philo)
{
	size_t	time;

	time = calc_time(philo->vars);
	if (time - philo->eat_time >= (size_t)philo->vars->time_to_die)
		return (1);
	return (0);
}

int	*monitoring(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->vars->monitor_sem);
		if (check_death(philo))
			break ;
		sem_post(philo->vars->monitor_sem);
		wait_time(philo, 5);
	}
	return (NULL);
}

int	create_monitor_sem(int philo, sem_t *monitor_sem)
{
	char	*id;
	char	*monitor;

	id = p_itoa(philo);
	monitor = p_strjoin("monitor_sem", id);
	free(id);
	monitor_sem = sem_open(monitor, O_CREAT, 0644, 0);
	if (monitor_sem == SEM_FAILED)
	{
		printf("Error creating %s\n", monitor);
		free(monitor);
		return (-1);
	}
	sem_unlink(monitor);
	free(monitor);
	return (0);
}

void	exit_error(t_philo *philo)
{
	sem_close(philo->vars->game_sem);
	sem_close(philo->vars->forks_sem);
	sem_close(philo->vars->eat_sem);
	exit(-1);
}

void	open_sems(t_vars *vars)
{
	vars->game_sem = sem_open("game_sem", 0);
	if (vars->game_sem == SEM_FAILED)
	{
		printf("Error opening game_sem\n");
		exit(-1);
	}
	vars->game_sem = sem_open("forks_sem", 0);
	if (vars->forks_sem == SEM_FAILED)
	{
		printf("Error opening forks_sem\n");
		sem_close(vars->forks_sem);
		exit(-1);
	}
	vars->game_sem = sem_open("eat_sem", 0);
	if (vars->eat_sem == SEM_FAILED)
	{
		printf("Error opening eat_sem\n");
		sem_close(vars->forks_sem);
		sem_close(vars->eat_sem);
		exit(-1);
	}
}

void	child(t_philo *philo)
{
	pthread_t	thread;
	sem_t		*monitor_sem;

	monitor_sem = NULL;
	open_sems(philo->vars);
	if (pthread_create(&thread, NULL, routine, philo))
		exit_error(philo);
	if (create_monitor_sem(philo->philo, monitor_sem))
		exit_error(philo);
	monitoring(philo);
	sem_close(philo->vars->game_sem);
	sem_close(philo->vars->forks_sem);
	sem_close(philo->vars->eat_sem);
	exit(philo->philo);
}
