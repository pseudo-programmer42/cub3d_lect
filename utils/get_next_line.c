/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 20:17:42 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/10 18:16:14 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define EOF_REACHED 0
#define NL_EXIST	1
#define ERROR		-1
#define BUFFER_SIZE	2048

static int		check_newline(char **saved, char *ptr, char **line)
{
	char		*temp;

	if (ptr != 0)
	{
		*line = ft_strndup(*saved, ptr - *saved);
		temp = ft_strndup(ptr + 1, ft_strlen(ptr + 1));
		free(*saved);
		*saved = temp;
		return (NL_EXIST);
	}
	if (*saved != 0)
	{
		*line = *saved;
		*saved = 0;
	}
	else
		*line = ft_strndup("", 0);
	return (EOF_REACHED);
}

int				get_next_line(int fd, char **line)
{
	static char *saved;
	char		buf[BUFFER_SIZE + 1];
	char		*temp;
	char		*nl_ptr;
	ssize_t		len;

	if (fd < 0 || line == 0)
		return (ERROR);
	if (saved == 0 && !(saved = ft_strndup("", 0)))
		return (ERROR);
	while ((nl_ptr = ft_strchr(saved, '\n')) == 0 &&
			(len = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[len] = 0;
		if (!(temp = ft_strjoin(saved, buf)))
			return (ERROR);
		if (saved != 0)
			free(saved);
		saved = temp;
	}
	if (len < 0)
		return (ERROR);
	return (check_newline(&saved, nl_ptr, line));
}
