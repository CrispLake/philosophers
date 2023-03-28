/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:56:24 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/28 16:50:00 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(philo->vars->game_sem);
	time = calc_time(philo->vars);
	if (!is_dead(time, philo->vars->time_to_die, philo->eat_time) && \
		vars->game_end != 1)
		printf("%lu %d %s\n", time, philo->philo, msg);
	else
		ret = 1;
	sem_post(philo->vars->game_sem);
	return (ret);
}

int	eat(t_philo *philo)
{
	sem_wait(philo->vars->forks_sem);
	sem_wait(philo->vars->forks_sem);
	if (print_state(philo, "is eating"))
		return (-1);
	sem_wait(philo->vars->monitor_sem);
	philo->eat_time = calc_time(philo->vars);
	philo->eat_times++;
	if (philo->eat_times == philo->vars->times_to_eat)
		sem_post(philo->vars->eat_sem);
	sem_post(philo->vars->monitor_sem);
	wait_time(philo, philo->vars->time_to_eat);
	sem_post(philo->vars->forks_sem);
	sem_post(philo->vars->forks_sem);
	return (0);
}

void	*routine_for_odds(t_philo *philo)
{
	int	x;

	x = 0;
	sem_wait(philo->vars->game_sem);
	sem_post(philo->vars->game_sem);
	calc_time(philo->vars);
	sem_post(philo->vars->monitor_sem);
	while (1)
	{
		if (print_state(philo, "is thinking"))
			return ((void *)&philo->philo);
		if (x++)
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
	sem_wait(philo->vars->game_sem);
	sem_post(philo->vars->game_sem);
	calc_time(philo->vars);
	sem_post(philo->vars->monitor_sem);
	while (1)
	{
		if (print_state(philo, "is thinking"))
			return ((void *)&philo->philo);
		if (!x++ && philo->philo % 2)
			wait_time(philo, philo->vars->time_to_eat - 5);
		if (eat(philo))
			return ((void *)&philo->philo);
		if (print_state(philo, "is sleeping"))
			return ((void *)&philo->philo);
		wait_time(philo, philo->vars->time_to_sleep);
	}
}
