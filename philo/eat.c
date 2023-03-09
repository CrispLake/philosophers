/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:26:34 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/09 11:08:17 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_philo *philo, t_fork **fork1, t_fork **fork2)
{
	if (philo->philo % 2)
	{
		(*fork1) = philo->right;
		(*fork2) = philo->left;
	}
	else
	{
		(*fork1) = philo->left;
		(*fork2) = philo->right;
	}
}

int	grab_forks(t_philo *philo)
{
	t_fork	*fork1;
	t_fork	*fork2;

	get_forks(philo, &fork1, &fork2);
	if (mutex_lock_error(fork1, 1))
		return (-1);
	if (function_in_mutex(NULL, philo, "has taken a fork"))
	{
		mutex_lock_error(fork1, 2);
		return (-1);
	}
	if (fork1 == fork2)
	{
		mutex_lock_error(fork1, 2);
		return (-1);
	}
	if (mutex_lock_error(fork2, 1))
		return (-1);
	if (function_in_mutex(NULL, philo, "has taken a fork"))
	{
		mutex_lock_error(fork1, 2);
		mutex_lock_error(fork2, 2);
		return (-1);
	}
	return (0);
}

void	update_eat(t_philo *philo)
{
	philo->eat_times++;
	philo->eat_time = calc_time(philo->vars);
	if (philo->eat_times == philo->vars->times_to_eat)
		philo->vars->eaten_enough++;
}

int	eat(t_philo *philo)
{
	if (grab_forks(philo))
		return (-1);
	if (function_in_mutex(update_eat, philo, "is eating"))
		return (-1);
	wait_time(philo, philo->vars->time_to_eat);
	if (mutex_lock_error(philo->right, 2))
		return (-1);
	if (mutex_lock_error(philo->left, 2))
		return (-1);
	return (0);
}
