/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 16:04:40 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/27 18:19:40 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hyochoi_macros.h"

int			main(int argc, char *argv[])
{
	t_all	a;
	int		err;

	errno = 0;
/*
**		Check arguments, init structures and init mlx pointer
*/
	if ((argc == 3 && ft_strcmp(argv[2], "--save")) || argc < 2 || argc > 3)
		return (error_msg(INVALID_ARG));

	init_all(&a);

	if (!(a.mlx.mlx = mlx_init()))
		return (error_msg(MLX_ERROR));
/*
**		Parse map file
*/
	if ((err = parse_map(argv[1], &a)))
		return (error_msg(err));

	printf(PRINT_COLOR_GREEN"parsing done!"PRINT_COLOR_RESET"\n");

/*
**	minckim's code start-------------------------------------------------------
*/
	t_runtime	r;
	convert_data(&r, &a);
	
	if (argc == 3)
		return ((err = save_bmp(&r)) == 0 ? 0 : error_msg(err));

	mlx_hook(r.screen.win, 2, 1, key_press_manager, &r.key);
	mlx_hook(r.screen.win, 3, 2, key_release_manager, &r.key);
	mlx_hook(r.screen.win, 17, 1L << 5, cub_close, 0);
	mlx_loop_hook(r.screen.mlx, play, &r);
	mlx_loop(r.screen.mlx);
/*
**	minckim's code end---------------------------------------------------------
*/
	return (0);
}
