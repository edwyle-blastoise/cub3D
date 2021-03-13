# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/19 15:02:16 by eblastoi          #+#    #+#              #
#    Updated: 2020/11/27 19:39:15 by eblastoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_strlen.c ft_tolower.c ft_toupper.c ft_isalnum.c ft_isdigit.c ft_isalpha.c ft_isascii.c ft_isprint.c ft_memset.c ft_bzero.c ft_atoi.c ft_memcpy.c ft_memccpy.c ft_strncmp.c ft_strdup.c ft_calloc.c ft_memcmp.c ft_memchr.c ft_memmove.c ft_substr.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_strtrim.c ft_strjoin.c ft_split.c ft_itoa.c ft_strmapi.c

BONUS_SRCS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c

HEADERS		= libft.h

ifdef BONUS
	OBJS = ${OBJS} ${BONUS_OBJS}
else
	OBJS = ${OBJS}
endif

OBJS	= ${SRCS:.c=.o}

BONUS_OBJS	= ${BONUS_SRCS:.c=.o}

NAME		= libft.a

CC			= gcc

AR			= ar rcs

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

%.o:		%.c ${HEADERS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${AR} ${NAME} ${OBJS}

all:		${NAME}

bonus:		${OBJS} ${BONUS_OBJS}
			${AR} ${NAME} ${OBJS} ${BONUS_OBJS}

clean:
			${RM} ${OBJS}
			${RM} ${BONUS_OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
