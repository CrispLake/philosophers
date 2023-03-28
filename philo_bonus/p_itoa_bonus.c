/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_itoa_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:50:30 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/28 11:52:38 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*p_strrev(char *src)
{
	char	tmp;
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = p_strlen(src) - 1;
	while (i < i2)
	{
		tmp = src[i];
		src[i++] = src[i2];
		src[i2--] = tmp;
	}
	return (src);
}

static	int	p_calc_digits(int n)
{
	int	count;

	count = 2;
	if (n < 0)
		count++;
	while (n > 9 || n < -9)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static	void	p_terminator(char *s, int check)
{
	if (check)
		*s++ = '-';
	*s = 0;
}

char	*p_itoa(int n)
{
	char	*s;
	char	*save;
	int		check;

	check = 0;
	s = p_calloc(p_calc_digits(n), sizeof(char));
	if (!s)
		return (0);
	save = s;
	if (n == 0)
		*s++ = '0';
	if (n < 0)
	{
		check = 1;
		*s++ = ((n % 10) * -1) + '0';
		n /= -10;
	}
	while (n > 0)
	{
		*s++ = (n % 10) + '0';
		n /= 10;
	}
	p_terminator(s, check);
	return (p_strrev(save));
}
