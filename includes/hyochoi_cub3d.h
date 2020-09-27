/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyochoi_cub3d.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 23:06:43 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/27 18:19:32 by hyochoi          ###   ########.fr       */
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
** ============================================================================
** structures
** ============================================================================
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
	t_key			key;
	t_player		pl;
	t_mlx			mlx;
	t_map			map;
	t_img			img;
	t_img			tex[TEXNUM_MAX];
}					t_all;

typedef struct		s_mapcheck
{
	int				err_cnt;
	int				len_for;
	int				len_back;
	int				len_cur;
	int				n;
}					t_mapcheck;

/*
**	===========================================================================
**					init_all.c
*/
void				init_all(t_all *a);
/*
**	===========================================================================
**					parse_all.c
*/
int					parse_map(char *filename, t_all *a);
/*
**	===========================================================================
**					parse_tool.c
*/
int					parse_tex(char *line, int num, t_all *a);
int					parse_resol(char *line, t_all *a);
int					parse_color(char *line, int n, t_all *a);
int					map_valid_check(t_all *a);
/*
**	===========================================================================
**					print_msg.c
*/
int					error_msg(int num);
/*
**	===========================================================================
**					save_bmp.c
*/
# ifndef MINCKIM_STRUCT
#  define MINCKIM_STRUCT
typedef struct  	s_vec{
	double			x; 
	double			y; 
}					t_vec;

typedef struct  	s_ray{
	t_vec			dir;
	double			distance;
}					t_ray;

typedef struct  	s_pixel{
	double			distance;
	unsigned int	*color;
}					t_pixel;

typedef struct  	s_screen{
	void			*mlx;
	void			*win;
	t_img			img;
	t_pixel			**pixel;
	t_vec			origin;
	t_vec			dir;
	t_vec			plane;
	double			sin_unit;
	double			cos_unit;
	double			distance;
	t_ray			*ray;
	int				w;
	int				h;
}					t_screen;

typedef struct		s_entity{
	t_vec			a;
	t_vec			b;
	t_img			*texture;
}					t_entity;

typedef struct		s_runtime{
	t_screen		screen;
	t_vec			player_origin;
	t_vec			player_dir;
	t_vec			player_plane;
	t_img			texture[TEXNUM_MAX];
	t_entity		*wall;
	t_entity		*sprite;
	t_key			key;
	int				color_floor;
	int				color_ceiling;
}					t_runtime;
# endif
t_screen			*draw_frame(t_runtime *r);
int					save_bmp(t_runtime *r);

#endif
