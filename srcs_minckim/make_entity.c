#include "minckim_cub3d.h"
#include "minckim_macros.h"

int			get_entity_num(char **map, char c)
{
	int		size;
	char	*tmp;

	size = 0;
	while (*map)
	{
		tmp = *map++;
		while (*tmp)
			if (*tmp++ == c)
				size++;
	}
	return (size);
}

t_entity	entity_new(t_vec a, t_vec b, t_img *texture)
{
	t_entity	result;

	result.a = a;
	result.b = b;
	result.texture = texture;
	return (result);
}

t_entity	*make_wall_from_a_point(int x, int y, t_entity *start, t_img *tex)
{
	t_vec	btm_l;
	t_vec	btm_r;
	t_vec	top_l;
	t_vec	top_r;

	btm_l = vec_new(x * WALL_W			, y * WALL_W);
	btm_r = vec_new(x * WALL_W + WALL_W	, y * WALL_W);
	top_l = vec_new(x * WALL_W			, y * WALL_W + WALL_W);
	top_r = vec_new(x * WALL_W + WALL_W	, y * WALL_W + WALL_W);
	start[0] = entity_new(btm_r, top_r, tex + EAST);
	start[1] = entity_new(top_r, top_l, tex + NORTH);
	start[2] = entity_new(top_l, btm_l, tex + WEST);
	start[3] = entity_new(btm_l, btm_r, tex + SOUTH);
	return start + 4;
}

t_entity	*make_wall(char **map, t_img *texture)
{
	t_entity	*entity;
	t_entity	*entity_tmp;
	int			x;
	int			y;

	entity = malloc(sizeof(t_entity) * (get_entity_num(map, '1') * 4 + 1));
	entity_tmp = entity;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '1')
			{
				entity = make_wall_from_a_point(x, y, entity, texture);
			}
	}
	entity->texture = 0;
	return entity_tmp;
}

t_entity	*make_sprite(char **map, t_img *texture)
{
	t_entity	*entity;
	t_entity	*entity_tmp;
	int			size;
	int			x;
	int			y;

	size = get_entity_num(map, '2');
	entity = malloc(sizeof(t_entity) * (size + 1));
	entity_tmp = entity;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '2')
			{
				*entity = entity_new(\
					vec_new(x * WALL_W + WALL_W / 2, y * WALL_W + WALL_W / 2), \
					vec_new(0, 0), \
					texture + SPRITE);
				entity++;
			}
	}
	entity->texture = 0;
	return (entity_tmp);
}