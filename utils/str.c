/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:55:45 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/10 18:16:26 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t		ft_strlen(const char *s)
{
	size_t		len;

	len = 0;
	while (s[len])
	{
		len++;
	}
	return (len);
}

char		*ft_strchr(const char *s, int c)
{
	size_t		i;
	size_t		len;

	if (s == 0)
		return (0);
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

char		*ft_strndup(char *str, size_t len)
{
	char		*newstr;
	size_t		i;

	i = 0;
	if (!(newstr = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len)
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = 0;
	return (newstr);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char		*newstr;
	char		*tmp;
	size_t		len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(newstr = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	tmp = newstr;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = 0;
	return (newstr);
}

int			ft_strcmp(const char *s1, const char *s2)
{
	size_t		i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
