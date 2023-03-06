/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:24:25 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/06 17:04:35 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_taken(t_fork *fork, int philo)
{
	pthread_mutex_lock(&fork->fork_mutex);
	(void)philo;
	// printf("philo %d | is taken: %d\n", philo, fork->fork_taken);
	// usleep(700);
	if (fork->fork_taken)
	{
		pthread_mutex_unlock(&fork->fork_mutex);
		return (-1);
	}
	fork->fork_taken = 1;
	pthread_mutex_unlock(&fork->fork_mutex);
	return (0);
}

int	grab_fork(t_philo *philo, int fork)
{
	if (philo->philo % 2)
	{
		if (fork == 1)
		{
			if (check_taken(philo->right, philo->philo))
				return (-1);
		}
		else
			if (check_taken(philo->left, philo->philo))
				return (-1);
	}
	else
	{
		if (fork == 1)
		{
			if (check_taken(philo->left, philo->philo))
				return (-1);
		}
		else
			if (check_taken(philo->right, philo->philo))
				return (-1);
	}
	return (0);
}

void	free_fork2(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork_mutex);
	fork->fork_taken = 0;
	pthread_mutex_unlock(&fork->fork_mutex);
}

void	free_fork(t_philo *philo, int fork)
{
	if (philo->philo % 2)
	{
		if (fork == 1)
			free_fork2(philo->right);
		else
		{
			free_fork2(philo->right);
			free_fork2(philo->left);
		}
	}
	else
	{
		if (fork == 1)
			free_fork2(philo->left);
		else
		{
			free_fork2(philo->left);
			free_fork2(philo->right);
		}
	}
}
