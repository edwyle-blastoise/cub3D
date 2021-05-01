SRCS		= srcs/cub3d.c \
			srcs/parser.c \
			srcs/define_params.c \
			srcs/player.c \
			srcs/create_map.c \
			srcs/raycasting.c \
			srcs/check_map.c \
			srcs/textures.c \
			srcs/draw.c \
			srcs/sprites.c \
			srcs/sprites_utils.c \
			srcs/screenshot_bmp.c \
			srcs/errors_and_exit.c \
			srcs/key_events.c \
			srcs/cub3d_utils.c \
			${GNL_DIR}/get_next_line.c \
			${GNL_DIR}/get_next_line_utils.c

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

CFLAGS		= -Wall -Wextra -Werror

MLX_FLAGS	= -framework OpenGL -framework AppKit

RM			= rm -f

all:		${NAME}

%.o:		%.c ${HEADERS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${LIBFT}:
			${MAKE} -j4 -C ${LIBFT_DIR} bonus

${LIBMLX}:
			${MAKE} -j4 -C ${MLX_DIR}

${NAME}:	${OBJS} ${LIBFT} ${LIBMLX}
			${CC} ${OBJS} ${LIBFT} ${LIBMLX} ${MLX_FLAGS} -o ${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} clean -C ${LIBFT_DIR}
			${MAKE} clean -C ${MLX_DIR}

fclean:		clean
			${RM} ${NAME}
			${MAKE} fclean -C ${LIBFT_DIR}

re:			fclean all

.PHONY:		all clean fclean re
