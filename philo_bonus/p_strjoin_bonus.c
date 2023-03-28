/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_strjoin_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:47:00 by emajuri           #+#    #+#             */
/*   Updated: 2023/03/28 12:04:16 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	p_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;

	slen = p_strlen(src);
	if (dstsize == 0)
		return (slen);
	while (dstsize-- > 1 && *src != 0)
		*dst++ = *src++;
	*dst = 0;
	return (slen);
}

char	*p_strjoin(char const *s1, char const *s2)
{
	size_t	sumlen;
	size_t	s1len;
	size_t	s2len;
	char	*s;

	if (!s1 || !s2)
		return (0);
	s1len = p_strlen(s1);
	s2len = p_strlen(s2);
	sumlen = s1len + s2len;
	s = p_calloc(sumlen, sizeof(char) + 1);
	if (s)
	{
		p_strlcpy(s, s1, (s1len + 1));
		p_strlcpy((s + s1len), s2, (s2len + 1));
		return (s);
	}
	return (0);
}
