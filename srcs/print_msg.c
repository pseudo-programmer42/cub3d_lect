/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 17:45:12 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/18 12:03:13 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hyochoi_macros.h"

static void	msg_one(int num)
{
	if (num == INVALID_ARG)
		write(1, "Invalid argument.\n", 18);
	else if (num == OPEN_ERROR)
		write(1, "Occured when opening a file.\n", 29);
	else if (num == GNL_ERROR)
		write(1, "Occured in GNL function.\n", 25);
	else if (num == INVALID_MAP)
		write(1, "Invalid map.\n", 13);
	else if (num == MALLOC_FAILED)
		write(1, "Malloc failed.\n", 15);
	else if (num == MULTIPLE_INFO)
		write(1, "Map has multiple information.\n", 30);
	else if (num == LACKING_INFO)
		write(1, "Not enough map information.\n", 28);
	else if (num == MLX_ERROR)
		write(1, "Occured in MLX function.\n", 25);
	else if (num == INAPP_VALUE)
		write(1, "Inappropriate value in map file.\n", 33);
	else if (num == TOO_SMALL_RES)
		write(1, "Too small resolution in map file.\n", 34);
}

static void	msg_two(int num)
{
	if (num == NOT_SURROUNDED)
		write(1, "Map is not surrounded by wall.\n", 31);
	else if (num == MULTI_PLAYER)
		write(1, "Map has multiple user location.\n", 32);
	else if (num == INVALID_COMP)
		write(1, "Map has an invalid component.\n", 30);
	else if (num == NO_PLAYER)
		write(1, "Map has no player.\n", 19);
}

int			error_msg(int num)
{
	write(1, PRINT_COLOR_RED, 6);
	write(1, "Error\n", 6);
	write(1, PRINT_COLOR_RESET, 5);
	if (num >= -10)
		msg_one(num);
	else
		msg_two(num);
	if (errno != 0 && errno != 60)
		perror("");
	exit(num);
}
