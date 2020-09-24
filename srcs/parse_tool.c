/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:28:30 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/25 01:16:04 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hyochoi_macros.h"

int			parse_tex(char *line, int n, t_all *a)
{
	int		i;
	int		fd;
	char	*filename;

	i = 0;
/*
**		If there is a duplicate texture data, return error
*/
	if (a->tex[n].addr != 0)
		return (MULTIPLE_INFO);

	line = skip_(SPACE, line);
/*
**		Parse filename and line validity check
*/
	if (!(filename = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1))))
		return (MALLOC_FAILED);

	while (*line != ' ' && *line != '\0')
		filename[i++] = *(line++);
	filename[i] = '\0';
	
	if ((line = skip_(SPACE, line)) && *line != '\0')
		return (INAPP_VALUE);

	if (((fd = open(filename, O_RDONLY)) < 0))
	{
		free(filename); 
		return (OPEN_ERROR);
	}
/*
**		If filename is valid, convert xpm file to image and make a texture array.
**		We will only use the array. So free image pointer.
*/
	if (!(a->tex[n].ptr = mlx_xpm_file_to_image(a->mlx.mlx, filename, &(a->tex[n].w), &(a->tex[n].h))) ||
		!(a->tex[n].addr = (unsigned int *)mlx_get_data_addr(a->tex[n].ptr,
							&(a->tex[n].bits_per_pixel), &(a->tex[n].size_line), &(a->tex[n].endian))))
	{
		if (a->tex[n].ptr != 0)
			free(a->tex[n].ptr);
		free(filename);
		close(fd);
		return (MLX_ERROR);
	}

	free(a->tex[n].ptr);
	a->tex[n].ptr = 0;
	free(filename);
	close(fd);

	return (0);
}

int			parse_color(char *line, int n, t_all *a)
{
	int r;
	int g;
	int b;

/*
**		If cub3d have parsed color data, return error
*/
	if (a->map.color_flag[n] != 0)
		return (MULTIPLE_INFO);
	a->map.color_flag[n] = 1;

	line = skip_(SPACE, line);

/*
**		Parse R, G, B value
*/
	r = ft_atoi(line);

	line = skip_(NUM, line);
	if ((line = skip_(SPACE, line)) && *line != ',')
		return (INAPP_VALUE);
	line = skip_(SPACE, ++line);

	g = ft_atoi(line);

	line = skip_(NUM, line);
	if ((line = skip_(SPACE, line)) && *line != ',')
		return (INAPP_VALUE);
	line = skip_(SPACE, ++line);

	b = ft_atoi(line);

	line = skip_(NUM, line);
	if (((line = skip_(SPACE, line)) && *line != '\0') ||
		(r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255))
		return (INAPP_VALUE);
	a->map.color[n] += r * 256 * 256 + g * 256 + b;

	return (0);
}

int			parse_resol(char *line, t_all *a)
{
/*
**		If cub3d have parsed resolution data, return error
*/
	if (a->img.w || a->img.h)
		return (MULTIPLE_INFO);

	line = skip_(SPACE, line);

/*
**		Parse resolution value
*/
	a->img.w = ft_atoi(line);

	line = skip_(NUM, line);
	line = skip_(SPACE, line);

	a->img.h = ft_atoi(line);
	
	line = skip_(NUM, line);
	line = skip_(SPACE, line);
	if (*line != '\0')
		return (INAPP_VALUE);

/*
**		Check resolution validity and change value
*/
	if (a->img.w <= 0 || a->img.h <= 0)
		return (INAPP_VALUE);
	if (a->img.w < WIN_W_MIN || a->img.h < WIN_H_MIN)
		return (TOO_SMALL_RES);

	if (a->img.w > WIN_W_MAX)
		a->img.w = WIN_W_MAX;
	if (a->img.h > WIN_H_MAX)
		a->img.h = WIN_H_MAX;

	return (0);
}

static int	map_closed_check(t_all *a, t_mapcheck *m, int i, int j)
{
	int		err;

/*
**		Check given j, i's surroundings with forward, back line length
*/
	err = 0;
	if (j > 0 && m->len_for > i - 1)
		err += a->map.map[j - 1][i - 1] == ' ' ? 1 : 0;
	if (j > 0 && m->len_for > i)
		err += a->map.map[j - 1][i] == ' ' ? 1 : 0;
	if (j > 0 && m->len_for > i + 1)
		err += a->map.map[j - 1][i + 1] == ' ' ? 1 : 0;
	if (i > 0)
		err += a->map.map[j][i - 1] == ' ' ? 1 : 0;
	if (i < m->len_cur)
		err += a->map.map[j][i + 1] == ' ' ? 1 : 0;
	if (j < a->map.h - 1 && m->len_back > i - 1)
		err += a->map.map[j + 1][i - 1] == ' ' ? 1 : 0;
	if (j < a->map.h - 1 && m->len_back > i)
		err += a->map.map[j + 1][i] == ' ' ? 1 : 0;
	if (j < a->map.h - 1 && m->len_back > i + 1)
		err += a->map.map[j + 1][i + 1] == ' ' ? 1 : 0;
	return (err > 0 ? NOT_SURROUNDED : 0);
}

int			map_valid_check(t_all *a)
{
	t_mapcheck	m;
	int			i;
	int			j;
	int			err;
	char		tmp;

	j = 0;
	m.err_cnt = 0;
	while (a->map.map[j] != 0)
	{
/*
** 			In this check function, I suggested non-rectangle map input(with no padding).
** 			So we need fore, back line's length to prevent SEGFAULT.
*/
		i = 0;
		if (j != 0)
			m.len_for = ft_strlen(a->map.map[j - 1]);
		if (j < a->map.h - 1)
			m.len_back = ft_strlen(a->map.map[j + 1]);
		m.len_cur = ft_strlen(a->map.map[j]);

		while (a->map.map[j][i] != 0)
		{
			tmp = a->map.map[j][i];
/*
** 				Check map components.
**				If there is invalid component in a map or multiple user location,
**				return error.
*/
			if (tmp == 'W' || tmp == 'E' || tmp == 'S' || tmp == 'N')
			{
				a->pl.pos_x = (double)i + 0.5;
				a->pl.pos_y = (double)j + 0.5;
				a->map.dir_init = tmp;
				a->map.pl_num++;
				if (a->map.pl_num > 1)
					return (MULTI_PLAYER);
			}
			if (!(tmp == ' ' || tmp == '0' || tmp == '1' || tmp == '2'
				|| tmp == 'W' || tmp == 'E' || tmp == 'S' || tmp == 'N'))
				return (INVALID_COMP);
/*
**				When given j, i's value is neither space nor wall,
**				check if a map is closed.
*/
			if (tmp != ' ' && tmp != '1')
			{
				if (j == 0 || j == a->map.h - 1 || i == 0 || i == m.len_cur - 1)
					return (NOT_SURROUNDED);
				if ((err = map_closed_check(a, &m, i, j)) != 0)
					return (NOT_SURROUNDED);
			}
			i++;
		}
		j++;
	}
	return (a->map.pl_num == 0 ? NO_PLAYER : 0);
}
