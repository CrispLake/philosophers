/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:52:12 by emajuri           #+#    #+#             */
/*   Updated: 2023/02/28 14:05:00 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_bzero(void *s, size_t n)
{
	char	*p;

	p = s;
	while (n-- > 0)
		*p++ = 0;
}

void	*p_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	p_bzero(ptr, (count * size));
	return ((void *)ptr);
}

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

