#include "minckim_cub3d.h"
#include "minckim_macros.h"

void	refresh_screen(t_pixel **pixel, int w, int h)
{
	int		y;
	int		x;
	t_pixel	*tmp;

	x = -1;
	while (++x < w)
	{
		y = -1;
		while (++y < h)
		{
			tmp = pixel[x] + y;
			tmp->distance = INFINITY;
			*(tmp->color) = COLOR_DEFAULT;
		}
	}
}

void	refresh_ray(t_ray *ray, t_vec *dir, t_vec *plane, int w)
{
	int		x;
	t_vec	plane_tmp;

	plane_tmp = vec_mul(*plane, -(double)w / 2);
	ray[0].distance = INFINITY;
	ray[0].dir = vec_add(*dir, plane_tmp);
	x = 0;
	while (++x < w)
	{
		ray[x].dir = vec_add(ray[x - 1].dir, *plane);
		ray[x].distance = INFINITY;
	}
}

int		play(t_runtime *r)
{
	t_screen	*s;

	s = &r->screen;
	refresh_screen(s->pixel, s->w, s->h);
	player_move(r);
	s->origin = r->player_origin;
	s->dir = r->player_dir;
	s->plane = r->player_plane;
	refresh_ray(s->ray, &s->dir, &s->plane, s->w);
	draw_floor(s, r->color_floor, r->color_ceiling);
	draw_wall(&r->screen, r->wall);
	draw_sprite(&r->screen, r->sprite);
	mlx_put_image_to_window(r->screen.mlx, r->screen.win, r->screen.img.ptr, 0, 0);
	return 0;
}