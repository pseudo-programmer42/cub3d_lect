#include "minckim_cub3d.h"
#include "minckim_macros.h"

t_vec	get_width_range(t_screen *screen, t_entity *wall)
{
	// t_vec	result;
	// t_vec	result_a;
	// t_vec	result_b;
	// t_vec	constant;

	// constant = vec_sub(&wall->a, &screen->origin);
	// result_a = equation_solver(&screen->dir, &screen->plane, &constant);
	// constant = vec_sub(&wall->b, &screen->origin);
	// result_b = equation_solver(&screen->dir, &screen->plane, &constant);
	// result.x = 0;
	// result.y = 0;
	// if (result_a.x < 0 && result_b.x < 0)
	// 	return (result);
	// else if (result_a.x < 0 || result_a.x < 0)
	// 	result.y = screen->w;
	// else
	// {
	// 	result.x = result_a.y / result_a.x + screen->w / 2;
	// 	result.y = result_b.y / result_b.x + screen->w / 2;
	// 	if (result.x > result.y)
	// 	{
	// 		double tmp = result.y;
	// 		result.y = result.x;
	// 		result.x = tmp;
	// 	}
	// 	result.y += 1;
	// 	result.x = result.x < 0 ? 0 : result.x;
	// 	result.y = result.y > screen->w - 1 ? screen->w - 1 : result.y;
	// 	// result.y = screen->w;
	// }
	// return (result);
	t_vec	result;
	(void)wall;
	result.x = 0;
	result.y = screen->w - 1;
	return result;
}

t_vec	ray_x_face(t_ray *ray, t_entity *wall, t_vec *origin)
{
	t_vec	coeff;
	t_vec	constant;

	coeff = vec_sub(wall->a, wall->b);
	constant = vec_sub(wall->a, *origin);
	return (equation_solver(&ray->dir, &coeff, &constant));
}

void	draw_vertical(t_screen *screen, t_entity *wall, t_vec *hit_info, int x)
{
	int				screen_y0;
	int				screen_y1;
	int				screen_y_h;
	int				texture_x;
	int				texture_y;
	unsigned int	color;

	texture_x = hit_info->y * wall->texture->w;
	screen_y0 = -(WALL_H - EYE_LEVEL) / hit_info->x * screen->distance + screen->h / 2;
	screen_y1 = (EYE_LEVEL) / hit_info->x * screen->distance + screen->h / 2;
	screen_y_h = screen_y1 - screen_y0;
	screen_y0 = screen_y0 < 0 ? 0 : screen_y0;
	while (screen_y0 < screen_y1 && screen_y0 < screen->h)
	{
		// 곱셈 및 나눗셈 순서에 주의!!
		texture_y = wall->texture->h - (screen_y1 - screen_y0) * wall->texture->h / screen_y_h;
		if (texture_y < 0 || wall->texture->h <= texture_y)
		{
			screen_y0++;
			continue ;
		}
		if ((color = img_pick_color(wall->texture, texture_x, texture_y)) \
		 != 0xff000000)
		{
			*(screen->pixel[x][screen_y0].color) = color;
			screen->pixel[x][screen_y0].distance = hit_info->x;
		}
		screen_y0++;
	}
}

void	draw_wall(t_screen *screen, t_entity *wall)
{
	t_vec	range;
	int		x;
	int		x_max;
	t_vec	hit_info;
	t_ray	*ray;

	while (wall->texture)
	{
		range = get_width_range(screen, wall);
		x = (int)range.x;
		x_max = (int)range.y;
		while (x < x_max)
		{
			ray = screen->ray + x;
			hit_info = ray_x_face(ray, wall, &screen->origin);
			if (0 < hit_info.x && 0 <= hit_info.y && hit_info.y <= 1)
			{
				if (hit_info.x < ray->distance)
				{
					ray->distance = hit_info.x;
					draw_vertical(screen, wall, &hit_info, x);
				}
			}
			x++;
		}
		wall++;
	}
	// t_vec	range;
	// int		min;
	// int		max;
	// t_vec	hit_info;
	// t_ray	*ray;

	// while (wall->texture)
	// {
	// 	range = get_width_range(screen, wall);
	// 	min = (int)range.x;
	// 	max = (int)range.y;
	// 	while (min < max)
	// 	{
	// 		ray = screen->ray + min;
	// 		hit_info = ray_x_face(ray, wall, &screen->origin);
	// 		if (0 < hit_info.x && 0 <= hit_info.y && hit_info.y <= 1)
	// 		{
	// 			if (hit_info.x < ray->distance)
	// 			{
	// 				ray->distance = hit_info.x;
	// 				draw_vertical(screen, wall, &hit_info, min);
	// 			}
	// 		}
	// 		min++;
	// 	}
	// 	wall++;
	// }
}

void	draw_sprite(t_screen *screen, t_entity *sprite)
{
	t_entity	sprite_tmp;
	t_vec		dir;
	t_vec		range;
	int			min;
	int			max;
	t_vec		hit_info;
	t_ray		*ray;

	sprite_tmp.texture = sprite->texture;
	dir.x = -screen->dir.y * WALL_W / 2;
	dir.y = screen->dir.x * WALL_W / 2;
	while (sprite->texture)
	{
		sprite_tmp.a = vec_add(sprite->a, dir);
		sprite_tmp.b = vec_sub(sprite->a, dir);
		range = get_width_range(screen, &sprite_tmp);
		min = (int)range.x;
		max = (int)range.y;
		while (min < max)
		{
			ray = screen->ray + min;
			hit_info = ray_x_face(ray, &sprite_tmp, &screen->origin);
			if (0 < hit_info.x && 0 <= hit_info.y && hit_info.y <= 1)
			{
				if (hit_info.x < ray->distance)
				{
					ray->distance = hit_info.x;
					draw_vertical(screen, &sprite_tmp, &hit_info, min);
				}
			}
			min++;
		}
		sprite++;
	}
}

void	draw_floor(t_screen *screen, int color_floor, int color_ceiling)
{
	int		x;
	int		y;
	t_pixel	**pixel;

	pixel = screen->pixel;
	y = -1;
	while (++y < screen->h / 2)
	{
		x = -1;
		while (++x < screen->w)
			*(pixel[x][y].color) = color_ceiling;
	}
	while (++y < screen->h)
	{
		x = -1;
		while (++x < screen->w)
			*(pixel[x][y].color) = color_floor;
	}
}