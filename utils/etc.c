/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 18:04:01 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/18 00:09:09 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hyochoi_macros.h"

int			ft_isblank(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (c);
	else
		return (0);
}

int			is_blank_line(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (ft_isblank(s[i++]))
			continue;
		else
			return (0);
	}
	return (1);
}

char		*skip_(int flag, char *str)
{
	if (flag == SPACE)
	{
		while (*str == ' ')
			str++;
	}
	else if (flag == NUM)
	{
		while (*str >= '0' && *str <= '9')
			str++;
	}
	return (str);
}

int			ft_atoi(const char *nptr)
{
	unsigned long long	result;
	size_t				i;
	int					minus;

	result = 0;
	minus = 1;
	i = 0;
	while (ft_isblank(*nptr))
	{
		nptr++;
	}
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		if (result > 4294967295)
			return (minus == 1 ? -1 : 0);
		i++;
	}
	return (result * minus);
}
