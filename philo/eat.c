/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:26:34 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/15 15:43:17 by emajuri          ###   ########.fr       */
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
	if (print_state(philo, "has taken a fork"))
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
	if (print_state(philo, "has taken a fork"))
	{
		mutex_lock_error(fork1, 2);
		mutex_lock_error(fork2, 2);
		return (-1);
	}
	return (0);
}

void	update_eat(t_philo *philo, size_t time)
{
	if (mutex_lock_error(&philo->philo_mutex, 1))
		return ;
	philo->eat_time = time;
	if (mutex_lock_error(&philo->philo_mutex, 2))
		return ;
	philo->eat_times++;
	if (philo->eat_times == philo->vars->times_to_eat)
		philo->vars->eaten_enough++;
}

int	eat(t_philo *philo)
{
	if (grab_forks(philo))
		return (-1);
	if (print_state(philo, "is eating"))
	{
		mutex_lock_error(philo->right, 2);
		mutex_lock_error(philo->left, 2);
		return (-1);
	}
	update_eat(philo, calc_time(philo->vars));
	wait_time(philo, philo->vars->time_to_eat);
	if (mutex_lock_error(philo->right, 2))
		return (-1);
	if (mutex_lock_error(philo->left, 2))
		return (-1);
	return (0);
}
