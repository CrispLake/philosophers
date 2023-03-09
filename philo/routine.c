/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:48:09 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/09 11:30:42 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	function_in_mutex(void f(t_philo *philo), t_philo *philo, const char *msg)
{
	t_vars	*vars;

	vars = philo->vars;
	if (mutex_lock_error(&philo->vars->game_mutex, 1))
		return (-1);
	if (f)
		f(philo);
	if (vars->game_end != 1)
		printf("%d %d %s\n", calc_time(vars), philo->philo, msg);
	else
	{
		if (mutex_lock_error(&philo->vars->game_mutex, 2))
			return (-1);
		return (1);
	}
	if (mutex_lock_error(&philo->vars->game_mutex, 2))
		return (-1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		x;

	x = 0;
	philo = (t_philo *)arg;
	if (mutex_lock_error(&philo->vars->game_mutex, 1))
		return (NULL);
	if (mutex_lock_error(&philo->vars->game_mutex, 2))
		return (NULL);
	while (1)
	{
		if (function_in_mutex(NULL, philo, "is thinking"))
			return (NULL);
		if (!x && philo->vars->philo_count % 2 == 0)
			if (philo->philo % 2)
				wait_time(philo, (philo->vars->time_to_eat / 2));
		if (x++ && philo->vars->philo_count % 2)
			wait_time(philo, philo->vars->time_to_eat);
		wait_time(philo, calc_time(philo->vars) % 8);
		if (eat(philo))
			return (NULL);
		if (function_in_mutex(NULL, philo, "is sleeping"))
			return (NULL);
		wait_time(philo, philo->vars->time_to_sleep);
	}
}
