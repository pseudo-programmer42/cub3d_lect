/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:12:34 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/27 18:19:24 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hyochoi_macros.h"

static void	bmp_type(t_screen *s, int fd)
{
	int				tmp;
	int				i;
	unsigned char	buf[14];

	i = 0;
	while (i < 14)
		buf[i++] = 0;
	buf[0] = (unsigned char)('B');
	buf[1] = (unsigned char)('M');
	tmp = 4 * (s->w * s->h) + 14 + 40;
	buf[2] = (unsigned char)(tmp % 256);
	buf[3] = (unsigned char)(tmp / 256 % 256);
	buf[4] = (unsigned char)(tmp / 256 / 256 % 256);
	buf[5] = (unsigned char)(tmp / 256 / 256 / 256);
	buf[10] = (unsigned char)(54);
	write(fd, buf, 14);
}

static void	bmp_info(t_screen *s, int fd)
{
	int				i;
	unsigned char	buf[40];

	i = 0;
	while (i < 40)
		buf[i++] = 0;
	buf[0] = (unsigned char)(40);
	buf[4] = (unsigned char)(s->w % 256);
	buf[5] = (unsigned char)(s->w / 256 % 256);
	buf[6] = (unsigned char)(s->w / 256 / 256 % 256);
	buf[7] = (unsigned char)(s->w / 256 / 256 / 256);
	buf[8] = (unsigned char)(s->h % 256);
	buf[9] = (unsigned char)(s->h / 256 % 256);
	buf[10] = (unsigned char)(s->h / 256 / 256 % 256);
	buf[11] = (unsigned char)(s->h / 256 / 256 / 256);
	buf[12] = (unsigned char)(1);
	buf[14] = (unsigned char)(32);
	write(fd, buf, 40);
}

static void	bmp_data(t_screen *s, int fd)
{
	int				tmp;
	int				i;
	int				j;
	unsigned char	buf[4];

	j = s->h - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < s->w)
		{
			tmp = s->img.addr[i + j * s->w];
			buf[0] = (unsigned char)(tmp % 256);
			buf[1] = (unsigned char)(tmp / 256 % 256);
			buf[2] = (unsigned char)(tmp / 256 / 256);
			buf[3] = (unsigned char)(0);
			write(fd, buf, 4);
			i++;
		}
		j--;
	}
}

int			save_bmp(t_runtime *r)
{
	int			i;
	int			fd;
	t_screen	*s;

	i = 0;
	s = draw_frame(r);
	if (!(fd = open("img.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0700)))
		return (OPEN_ERROR);
	bmp_type(s, fd);
	bmp_info(s, fd);
	bmp_data(s, fd);
	close(fd);
	cub_close();
	return (0);
}
