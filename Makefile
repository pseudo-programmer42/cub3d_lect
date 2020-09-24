# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minckim <minckim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/10 13:28:31 by hyochoi           #+#    #+#              #
#    Updated: 2020/09/24 20:08:29 by minckim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
IMG = img.bmp
LIBMLX_DIR = mlx
MLX_FLAGS = -framework OpenGL -framework AppKit
# CFLAGS = -g
CFLAGS = -Wall -Wextra -Werror -g -O3
INCS = includes
SRCS_DIR = ./srcs/
SRCS_FILE = \
	cub3d.c			init_all.c 		key.c				parse_all.c	\
	parse_tool.c 	print_msg.c 	save_bmp.c \

SRCS_MINCKIM_DIR = ./srcs_minckim/
SRCS_MINCKIM_FILE = \
	convert.c		vector.c		make_entity.c 	init_pixel.c\
	raycast.c 		equation.c		play.c			player_move.c

SRCS = $(addprefix $(SRCS_DIR),$(SRCS_FILE)) \
	$(addprefix $(SRCS_MINCKIM_DIR),$(SRCS_MINCKIM_FILE))


OBJS = $(SRCS:.c=.o)
UTIL = ./utils/get_next_line.c ./utils/etc.c ./utils/list.c ./utils/str.c \
		./utils/ft_strdup.c
UTIL_O = $(UTIL:.c=.o)
HEADER =	./includes/cub3d.h ./includes/hyochoi_cub3d.h ./includes/utils.h \
			./includes/hyochoi_macros.h

.PHONY: all clean fclean re bonus norm

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(UTIL_O)
	@echo "\x1b[33m\nmaking libmlx.a ...\x1b[0m"
	@make all -s -C $(LIBMLX_DIR)/
	@echo "\x1b[33m\ncompling srcs ...\x1b[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(UTIL_O) -o $(NAME) -l$(LIBMLX_DIR) -L $(LIBMLX_DIR) $(MLX_FLAGS)
	@echo "\x1b[32m\ndone!\x1b[0m"
	@echo "\x1b[32m\nIf you want to check invalid maps simply, just\n\x1b[0m"
	@echo "\x1b[32mgit clone https://github.com/humblEgo/cub3D_map_tester.git\n\x1b[0m"
	@echo "\x1b[32mThis 'cub3D_map_tester' (by.iwoo) will help you.\n\x1b[0m"
	@echo "\x1b[32m\nUse map/map.cub to run cub3D (mandatory part)\n\x1b[0m"


run: $(NAME)
	./$(NAME) map/map.cub

clean:
	@echo "\x1b[33m\ncleaning object files...\x1b[0m"
	@/bin/rm -f $(OBJS) $(UTIL_O)
	@echo "\x1b[32m\ndone!\n\x1b[0m"

	# @make clean -s -C $(LIBMLX_DIR)/

fclean: clean
	@echo "\x1b[33m\ncleaning libmlx and cub3D...\x1b[0m"
	@/bin/rm -f $(NAME) $(IMG)
	@echo "\x1b[32m\ndone!\n\x1b[0m"

	# @make fclean -s -C $(LIBMLX_DIR)/

re: fclean all

norm:
	norminette $(SRCS) $(UTIL) $(HEADER)
