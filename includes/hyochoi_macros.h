/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyochoi_macros.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyochoi <hyochoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 17:16:42 by hyochoi           #+#    #+#             */
/*   Updated: 2020/09/18 12:44:59 by hyochoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HYOCHOI_MACROS_H
# define HYOCHOI_MACROS_H

# define WIN_W_MAX	2560
# define WIN_H_MAX	1400
# define WIN_W_MIN	640
# define WIN_H_MIN	480

# ifndef TEXNUM_MAX
#  define TEXNUM_MAX		5
# endif
# define INFO_PARSED	8
# define SPTEX_MAX		'S'

# define EAST			0
# define NORTH			1
# define SOUTH			2
# define WEST			3
# define SPRITE			4

# define WALK_SPEED 0.03
# define TURN_SPEED 0.05

# define EVENT_X_BUTTON		17
# define EVENT_KEY_PRESS	2
# define EVENT_KEY_RELEASE	3

# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_W		13
# define KEY_ESC	53
# define KEY_ARR_L	123
# define KEY_ARR_R	124

# define SPACE			0
# define NUM			1

# define GAME			0
# define SAVE			1

# define INVALID_ARG	-1
# define OPEN_ERROR		-2
# define GNL_ERROR		-3
# define INVALID_MAP	-4
# define MALLOC_FAILED	-5
# define MULTIPLE_INFO	-6
# define LACKING_INFO	-7
# define MLX_ERROR		-8
# define INAPP_VALUE	-9
# define TOO_SMALL_RES	-10
# define NOT_SURROUNDED	-11
# define MULTI_PLAYER	-12
# define INVALID_COMP	-13
# define NO_PLAYER		-14

# define FLOOR			0
# define CEIL			1

# define FRONT_BACK		0
# define LEFT_RIGHT		1

# define COLOR_WHITE	0x00ffffff
# define COLOR_RED		0x00ff0000
# define COLOR_GREEN	0x0000ff00
# define COLOR_BLUE		0x000000ff

# define PRINT_COLOR_RED	"\x1b[31m"
# define PRINT_COLOR_GREEN	"\x1b[32m"
# define PRINT_COLOR_YELLOW	"\x1b[33m"
# define PRINT_COLOR_BLUE	"\x1b[34m"
# define PRINT_COLOR_RESET	"\x1b[0m"

#endif
