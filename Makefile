SRCS		= cub3d.c parser.c define_params.c player.c create_map.c raycasting.c check_map.c textures.c draw.c sprites.c sprites_utils.c screenshot_bmp.c errors_and_exit.c key_events.c cub3d_utils.c \
			  ${GNL_DIR}/get_next_line.c ${GNL_DIR}/get_next_line_utils.c

HEADERS		= cub3d.h

OBJS		= ${SRCS:.c=.o}

MLX_DIR		= minilibx_opengl
LIBFT_DIR	= libft
GNL_DIR		= gnl

LIBFT		= ${LIBFT_DIR}/libft.a
LIBMLX		= ${MLX_DIR}/libmlx.a

INCLUDES	= -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(GNL_DIR)

NAME		= cub3D

CC			= gcc

CFLAGS		= -fsanitize=address -Wall -Wextra -Werror

MLX_FLAGS	= -framework OpenGL -framework AppKit

RM			= rm -f

%.o:		%.c ${HEADERS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${LIBFT}:
			${MAKE} -j4 -C ${LIBFT_DIR} bonus

${LIBMLX}:
			${MAKE} -j4 -C ${MLX_DIR}

${NAME}:	${OBJS} ${LIBFT} ${LIBMLX}
			${CC} ${OBJS} ${LIBFT} ${LIBMLX} ${MLX_FLAGS} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} clean -C ${LIBFT_DIR}
			${MAKE} clean -C ${MLX_DIR}

fclean:		clean
			${RM} ${NAME}
			${MAKE} fclean -C ${LIBFT_DIR}

re:			fclean all

.PHONY:		all clean fclean re
