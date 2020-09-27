#ifndef MINCKIM_CUB3D_H
# define MINCKIM_CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include "../includes/mlx.h"
# include "hyochoi_cub3d.h"

/*
** ============================================================================
** structures
** ============================================================================
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

/*
**	===========================================================================
**				m_convert.c
*/
void			convert_data();
/*
**	===========================================================================
**				m_init_pixel.c
*/
void			img_put_color();
unsigned int	img_pick_color(t_img *img, int x, int y);
t_pixel			**init_pixel();
/*
**	===========================================================================
**				m_equation.c
*/
t_vec			equation_solver(t_vec *coeff0, t_vec *coeff1, t_vec *constant);
/*
**	===========================================================================
**				m_make_entity.c
*/
t_entity		*make_wall();
t_entity		*make_sprite();
/*
**	===========================================================================
**				m_play.c
*/
int				play(t_runtime *r);
/*
**	===========================================================================
**				m_player_move.c
*/
int				key_press_manager(int key, t_key *key_storage);
int				key_release_manager(int key, t_key *key_storage);
int				player_move(t_runtime *r);
int				cub_close(void);
/*
**	===========================================================================
**				m_raycast.c
*/
void			draw_wall(t_screen *screen, t_entity *wall);
void			draw_sprite(t_screen *screen, t_entity *sprite);
void			draw_floor(t_screen *screen, int color_floor, int color_ceiling);
/*
**	===========================================================================
**				m_vector.c
*/
t_vec			vec_new(double a, double b);
t_vec			vec_add(t_vec a, t_vec b);
t_vec			vec_sub(t_vec a, t_vec b);
t_vec			vec_rot_min_cw(t_vec a);
t_vec			vec_rot_min_ccw(t_vec a);
t_vec			vec_mul(t_vec a, double b);
#endif