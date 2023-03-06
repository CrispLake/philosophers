/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_atoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:10:23 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/06 14:16:52 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_atoi(const char *str)
{
	int		negative;
	long	nb;

	negative = 1;
	nb = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{	
		if (*str == '-')
			negative = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - 48);
		str++;
	}
	nb *= negative;
	if (negative == 1 && nb < 0)
		return (-1);
	else if (negative == -1 && nb > 0)
		return (0);
	return (nb);
}

int	p_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (*s1 == *s2 && *s1 != 0 && *s2 != 0 && n > 1)
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

size_t	p_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

int	p_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	check_and_atoi(char *nb)
{
	int	i;

	i = 0;
	if (nb[i] == '+')
		i++;
	while (nb[i])
	{
		if (!p_isdigit(nb[i]))
			return (-1);
		i++;
	}
	i = p_strlen(nb);
	if (i > 10)
		return (-1);
	if (i == 10)
		if (p_strncmp(nb, "2147483647", 10) > 0)
			return (-1);
	return (p_atoi(nb));
}
