/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:48:09 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/15 15:47:27 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(size_t time, int time_to_die, int eat_time)
{
	if (time - eat_time >= (size_t)time_to_die)
		return (-1);
	return (0);
}

int	print_state(t_philo *philo, const char *msg)
{
	t_vars	*vars;
	size_t	time;
	int		ret;

	ret = 0;
	vars = philo->vars;
	if (mutex_lock_error(&philo->vars->game_mutex, 1))
		return (-1);
	time = calc_time(philo->vars);
	if (!is_dead(time, philo->vars->time_to_die, philo->eat_time) && 
		vars->game_end != 1 && vars->eaten_enough != vars->philo_count)
		printf("%lu %d %s\n", time, philo->philo, msg);
	else
		ret = 1;
	if (mutex_lock_error(&philo->vars->game_mutex, 2))
		return (-1);
	return (ret);
}

void	*routine_for_odds(t_philo *philo)
{
	int		x;

	x = 0;
	if (mutex_lock_error(&philo->vars->game_mutex, 1))
		return (NULL);
	if (mutex_lock_error(&philo->vars->game_mutex, 2))
		return (NULL);
	while (1)
	{
		if (print_state(philo, "is thinking"))
			return ((void *)&philo->philo);
		if (x++ && philo->vars->philo_count % 2)
			wait_time(philo, philo->vars->time_to_eat - 5);
		if (eat(philo))
			return ((void *)&philo->philo);
		if (print_state(philo, "is sleeping"))
			return ((void *)&philo->philo);
		wait_time(philo, philo->vars->time_to_sleep);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		x;

	x = 0;
	philo = (t_philo *)arg;
	if (philo->vars->philo_count % 2)
		return (routine_for_odds(philo));
	if (mutex_lock_error(&philo->vars->game_mutex, 1))
		return (NULL);
	if (mutex_lock_error(&philo->vars->game_mutex, 2))
		return (NULL);
	while (1)
	{
		if (print_state(philo, "is thinking"))
			return ((void *)&philo->philo);
		if (!x++ && philo->vars->philo_count % 2 == 0)
			if (philo->philo % 2)
				wait_time(philo, philo->vars->time_to_eat - 5);
		if (eat(philo))
			return ((void *)&philo->philo);
		if (print_state(philo, "is sleeping"))
			return ((void *)&philo->philo);
		wait_time(philo, philo->vars->time_to_sleep);
	}
}
