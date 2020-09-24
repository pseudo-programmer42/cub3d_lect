/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:07:42 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/17 23:30:27 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hyochoi_macros.h"

int			key_press(int key, t_all *a)
{
/*
**	if (key == KEY_ESC)
**		close_window(a);
*/
	if (key == KEY_A)
		a->key.a = 1;
	if (key == KEY_S)
		a->key.s = 1;
	if (key == KEY_D)
		a->key.d = 1;
	if (key == KEY_W)
		a->key.w = 1;
	if (key == KEY_ARR_L)
		a->key.arr_l = 1;
	if (key == KEY_ARR_R)
		a->key.arr_r = 1;
	return (0);
}

int			key_release(int key, t_all *a)
{
	if (key == KEY_A)
		a->key.a = 0;
	if (key == KEY_S)
		a->key.s = 0;
	if (key == KEY_D)
		a->key.d = 0;
	if (key == KEY_W)
		a->key.w = 0;
	if (key == KEY_ARR_L)
		a->key.arr_l = 0;
	if (key == KEY_ARR_R)
		a->key.arr_r = 0;
	return (0);
}
