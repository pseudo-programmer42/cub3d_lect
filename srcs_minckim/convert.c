#include "minckim_cub3d.h"
#include "minckim_macros.h"

t_vec	set_player_dir(t_map *map)
{
	if (map->dir_init == 'E')
		return vec_new(1, 0);
	if (map->dir_init == 'N')
		return vec_new(0, 1);
	if (map->dir_init == 'W')
		return vec_new(-1, 0);
	return vec_new(0, -1);
}

t_vec	set_player_plane(t_map *map, int w)
{
	double	min;

	min = tan(FOV / 2) / w * 2;
	if (map->dir_init == 'E')
		return vec_new(0, -min);
	if (map->dir_init == 'N')
		return vec_new(min, 0);
	if (map->dir_init == 'W')
		return vec_new(0, min);
	return vec_new(min, 0);
}

void	trans_map(t_map *raw)
{
	int		y;
	int		h;
	char	*tmp;
	char	**map;

	h = raw->h;
	y = 0;
	map = raw->map;
	while (y < h / 2)
	{
		tmp = map[y];
		map[y] = map[h - y - 1];
		map[h - y - 1] = tmp;
		y++;
	}
}

void	convert_data(t_runtime *r, t_all *a)
{
	int			i;
	t_screen	*s;

	s = &r->screen;
	s->mlx = a->mlx.mlx;
	s->img = a->img;
	s->w = a->img.w;
	s->h = a->img.h;
	s->win = mlx_new_window(s->mlx, s->w, s->h, "cub3D LESSON");
	s->img.ptr = mlx_new_image(s->mlx, s->w, s->h);
	s->img.addr = (unsigned int*)mlx_get_data_addr(s->img.ptr, \
		&(s->img.bits_per_pixel), &(s->img.size_line), &(s->img.endian));
	s->distance = 1 / tan(FOV / 2) * s->w / 2;
	s->pixel = init_pixel(s->w, s->h, &s->img);
	s->ray = malloc(sizeof(t_ray) * s->w);
	i = -1;
	while (++i < TEXNUM_MAX)
		r->texture[i] = a->tex[i];
	trans_map(&a->map);
	r->player_dir = set_player_dir(&a->map);
	r->player_plane = set_player_plane(&a->map, s->w);
	r->wall = make_wall(a->map.map, r->texture);
	r->sprite = make_sprite(a->map.map, r->texture);
	r->key = a->key;
	r->player_origin = vec_new(a->pl.pos_x * WALL_W, (a->map.h - a->pl.pos_y - 1) * WALL_W);
	r->color_floor = a->map.color[FLOOR];
	r->color_ceiling = a->map.color[CEILING];
}