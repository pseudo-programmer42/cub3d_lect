/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:12:34 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/17 23:34:46 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hyochoi_macros.h"

static void	bmp_type(t_all *a, int fd)
{
	int				tmp;
	int				i;
	unsigned char	buf[14];

	i = 0;
	while (i < 14)
		buf[i++] = 0;
	buf[0] = (unsigned char)('B');
	buf[1] = (unsigned char)('M');
	tmp = 4 * (a->img.w * a->img.h) + 14 + 40;
	buf[2] = (unsigned char)(tmp % 256);
	buf[3] = (unsigned char)(tmp / 256 % 256);
	buf[4] = (unsigned char)(tmp / 256 / 256 % 256);
	buf[5] = (unsigned char)(tmp / 256 / 256 / 256);
	buf[10] = (unsigned char)(54);
	write(fd, buf, 14);
}

static void	bmp_info(t_all *a, int fd)
{
	int				i;
	unsigned char	buf[40];

	i = 0;
	while (i < 40)
		buf[i++] = 0;
	buf[0] = (unsigned char)(40);
	buf[4] = (unsigned char)(a->img.w % 256);
	buf[5] = (unsigned char)(a->img.w / 256 % 256);
	buf[6] = (unsigned char)(a->img.w / 256 / 256 % 256);
	buf[7] = (unsigned char)(a->img.w / 256 / 256 / 256);
	buf[8] = (unsigned char)(a->img.h % 256);
	buf[9] = (unsigned char)(a->img.h / 256 % 256);
	buf[10] = (unsigned char)(a->img.h / 256 / 256 % 256);
	buf[11] = (unsigned char)(a->img.h / 256 / 256 / 256);
	buf[12] = (unsigned char)(1);
	buf[14] = (unsigned char)(32);
	write(fd, buf, 40);
}

static void	bmp_data(t_all *a, int fd)
{
	int				tmp;
	int				i;
	int				j;
	unsigned char	buf[4];

	j = a->img.h - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < a->img.w)
		{
			tmp = a->img.addr[i + j * a->img.w];
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

int			save_bmp(t_all *a)
{
	int		i;
	int		fd;
	int		tmp;

	i = 0;
	if (!(a->img.ptr = mlx_new_image(a->mlx.mlx, a->img.w, a->img.h))
		|| !(a->img.addr = (unsigned int *)mlx_get_data_addr(
		a->img.ptr, &tmp, &tmp, &tmp)))
		return (MLX_ERROR);
	//draw_screen(a, SAVE);
	fd = open("img.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0700);
	bmp_type(a, fd);
	bmp_info(a, fd);
	bmp_data(a, fd);
	close(fd);
	//close_window(a);
	return (0);
}
