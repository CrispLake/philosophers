/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_conversion_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:50:52 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/15 17:51:02 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_vars(t_vars *vars)
{
	if (vars->philo_count < 1)
	{
		printf("Incorrect philosopher count\n");
		vars->philo_count = -1;
	}
	if (vars->time_to_die < 1)
	{
		printf("Incorrect time_to_die\n");
		vars->philo_count = -1;
	}
	if (vars->time_to_eat < 1)
	{
		printf("Incorrect time_to_eat\n");
		vars->philo_count = -1;
	}
	if (vars->time_to_sleep < 1)
	{
		printf("Incorrect time_to_sleep\n");
		vars->philo_count = -1;
	}
	if (vars->times_to_eat == -1)
	{
		printf("Incorrect number_of_times_each_philosopher_must_eat\n");
		vars->philo_count = -1;
	}
}

void	init_vars(t_vars *vars, char **argv)
{
	vars->philo_count = check_and_atoi(argv[0]);
	vars->time_to_die = check_and_atoi(argv[1]);
	vars->time_to_eat = check_and_atoi(argv[2]);
	vars->time_to_sleep = check_and_atoi(argv[3]);
	if (argv[4])
		vars->times_to_eat = check_and_atoi(argv[4]);
	else
		vars->times_to_eat = -2;
	check_vars(vars);
}
