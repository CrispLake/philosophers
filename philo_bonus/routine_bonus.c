/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:41:16 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/11 14:41:18 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(int time, int time_to_die, int eat_time)
{
	if (time - eat_time >= time_to_die)
		return (-1);
	return (0);
}

int	function_in_mutex(void f(t_philo *philo), t_philo *philo, const char *msg)
{
	t_vars	*vars;
	int		time;
	int		ret;

	ret = 0;
	vars = philo->vars;
	if (mutex_lock_error(&philo->vars->game_mutex, 1))
		return (-1);
	time = calc_time(philo->vars);
	if (!is_dead(time, philo->vars->time_to_die, philo->eat_time) && 
		vars->game_end != 1 && vars->eaten_enough != vars->philo_count)
	{
		if (f)
			f(philo);
		printf("%d %d %s\n", time, philo->philo, msg);
	}
	else
		ret = 1;
	if (mutex_lock_error(&philo->vars->game_mutex, 2))
		return (-1);
	return (ret);
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
		if (eat(philo))
			return (NULL);
		if (function_in_mutex(NULL, philo, "is sleeping"))
			return (NULL);
		wait_time(philo, philo->vars->time_to_sleep);
	}
}
