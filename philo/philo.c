/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:54 by emajuri           #+#    #+#             */
/*   Updated: 2023/02/23 18:06:07 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	calc_time(t_vars *vars)
{
	size_t			time;
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	time = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
	if (vars->start_time == 0)
		vars->start_time = time;
	return (time - vars->start_time);
}

int	create_philo(int count, t_vars *vars)
{
	t_seat		*seat;

	seat = p_calloc(sizeof(t_seat), 1);
	seat->philo = count;
	if (pthread_mutex_init(&(seat->fork_mutex), NULL))
		return (-1);
	pthread_create(&(seat->thread), NULL, &routine, vars);
	return (0);
}

int	start_sim(t_vars *vars)
{
	int		count;

	count = 1;
	if (pthread_mutex_init(&(vars->game_mutex), NULL))
		return (-1);
	if (pthread_mutex_init(&(vars->print_mutex), NULL))
		return (-1);
	pthread_mutex_lock(&(vars->game_mutex));
	while (count <= vars->philo_count)
	{
		if (create_philo(count, vars))
			return (-1);
		count++;
	}
	pthread_mutex_unlock(&(vars->game_mutex));
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 5 || argc != 6)
	{
		printf("Incorrect argument count\n");
		return (0);
	}
	memset(&vars, 0, sizeof(t_vars));
	init_vars(&vars, argv + 1);
	if (vars.philo_count == -1)
		return (-1);
	if (start_sim(&vars))
		return (-1);
	while (vars.game_end != 1)
		;
	return (0);
}
