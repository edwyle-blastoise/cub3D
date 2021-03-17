/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:18:14 by eblastoi          #+#    #+#             */
/*   Updated: 2021/03/11 15:18:18 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include "minilibx_opengl/mlx.h"
#define SCALE 20
#define ENTER 36
#define ESC 53
#define W 13
#define A 0
#define S 1
#define D 2

typedef struct  s_params
{
    int         width;
    int         height;
    int         t;
    int         r;
    int         g;
    int         b;
    int         floor_color;
    int         ceilling_color;
    char        **map;
}               t_params;

typedef struct  s_point
{
    int         x;
    int         y;
}               t_point;

typedef struct s_player
{
    double x;
    double y;
    double direction;
}               t_player;

typedef struct  s_data
{
    void        *mlx;
    void        *win;
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

#endif