/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 20:13:39 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/18 12:47:57 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hyochoi_macros.h"

static void	init_img(t_all *a)
{
	int		i;

	i = 0;
	a->mlx.mlx = 0;
	a->mlx.win = 0;
	while (i < TEXNUM_MAX)
	{
		a->tex[i].h = 0;
		a->tex[i].w = 0;
		a->tex[i].bits_per_pixel = 0;
		a->tex[i].size_line = 0;
		a->tex[i].endian = 0;
		a->tex[i].ptr = 0;
		a->tex[i].addr = 0;
		i++;
	}
	a->img.ptr = 0;
	a->img.addr = 0;
	a->img.w = 0;
	a->img.h = 0;
}

static void	init_player(t_all *a)
{
	a->pl.pos_x = 0;
	a->pl.pos_y = 0;
}

static void	init_map(t_all *a)
{
	a->map.pl_num = 0;
	a->map.map = 0;
	a->map.list = 0;
	a->map.h = 0;
	a->map.info_num = 0;
	a->map.color[CEIL] = 0;
	a->map.color[FLOOR] = 0;
	a->map.color_flag[CEIL] = 0;
	a->map.color_flag[FLOOR] = 0;
	a->map.dir_init = 0;
}

static void	init_key(t_all *a)
{
	a->key.w = 0;
	a->key.s = 0;
	a->key.a = 0;
	a->key.d = 0;
	a->key.arr_l = 0;
	a->key.arr_r = 0;
}

void	init_all(t_all *a)
{
	init_img(a);
	init_player(a);
	init_map(a);
	init_key(a);
}
