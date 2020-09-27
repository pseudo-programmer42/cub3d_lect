#include "minckim_cub3d.h"
#include "minckim_macros.h"
#include "hyochoi_macros.h"

// copied from hyochoi
int		key_press_manager(int key, t_key *key_storage)
{
	if (key == KEY_A)
		key_storage->a = 1;
	if (key == KEY_S)
		key_storage->s = 1;
	if (key == KEY_D)
		key_storage->d = 1;
	if (key == KEY_W)
		key_storage->w = 1;
	if (key == KEY_ARR_L)
		key_storage->arr_l = 1;
	if (key == KEY_ARR_R)
		key_storage->arr_r = 1;
	if (key == KEY_ESC)
		cub_close();
	return (0);
}

int		key_release_manager(int key, t_key *key_storage)
{
	if (key == KEY_A)
		key_storage->a = 0;
	if (key == KEY_S)
		key_storage->s = 0;
	if (key == KEY_D)
		key_storage->d = 0;
	if (key == KEY_W)
		key_storage->w = 0;
	if (key == KEY_ARR_L)
		key_storage->arr_l = 0;
	if (key == KEY_ARR_R)
		key_storage->arr_r = 0;
	return (0);
}

int		player_move(t_runtime *r)
{
	t_vec	dir;
	t_vec	perp;

	dir = vec_mul(r->player_dir, MOVE_MIN);
	perp.x = -dir.y;
	perp.y = dir.x;
	if (r->key.w)
		r->player_origin = vec_add(r->player_origin, dir);
	if (r->key.a)
		r->player_origin = vec_add(r->player_origin, perp);
	if (r->key.s)
		r->player_origin = vec_sub(r->player_origin, dir);
	if (r->key.d)
		r->player_origin = vec_sub(r->player_origin, perp);
	if (r->key.arr_l)
	{
		r->player_dir = vec_rot_min_ccw(r->player_dir);
		r->player_plane = vec_rot_min_ccw(r->player_plane);
	}
	if (r->key.arr_r)
	{
		r->player_dir = vec_rot_min_cw(r->player_dir);
		r->player_plane = vec_rot_min_cw(r->player_plane);
	}
	return 0;
}

int		cub_close(void)
{
	printf("bye\n");
	exit(0);
}
