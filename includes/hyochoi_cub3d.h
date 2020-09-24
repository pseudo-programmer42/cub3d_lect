/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyochoi_cub3d.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 23:06:43 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/18 12:11:31 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HYOCHOI_CUB3D_H
# define HYOCHOI_CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include "utils.h"
# include "mlx.h"

#define TEXNUM_MAX 5

/*
** I got game textures from here https://opengameart.org/textures/all
*/

typedef struct		s_mlx
{
	void			*win;
	void			*mlx;
}					t_mlx;

typedef struct		s_img
{
	int				w;
	int				h;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	void			*ptr;
	unsigned int	*addr;
}					t_img;

typedef struct		s_map
{
	char			info_num;
	char			dir_init;
	int				h;
	int				color[2];
	int				color_flag[2];
	int				pl_num;
	t_list			*list;
	char			**map;
}					t_map;

typedef struct		s_player
{
	double			pos_x;
	double			pos_y;
}					t_player;

typedef struct		s_key
{
	char			w;
	char			s;
	char			a;
	char			d;
	char			arr_l;
	char			arr_r;
}					t_key;

typedef struct		s_all
{
	t_mlx			mlx;
	t_img			img;
	t_img			tex[TEXNUM_MAX];
	t_map			map;
	t_player		pl;
	t_key			key;
}					t_all;

typedef struct		s_mapcheck
{
	int				err_cnt;
	int				len_for;
	int				len_back;
	int				len_cur;
	int				n;
}					t_mapcheck;

void				init_all(t_all *a);

int					parse_map(char *filename, t_all *a);
int					parse_tex(char *line, int num, t_all *a);
int					parse_resol(char *line, t_all *a);
int					parse_color(char *line, int n, t_all *a);
int					map_valid_check(t_all *a);

int					error_msg(int num);

int					save_bmp(t_all *a);

#endif
