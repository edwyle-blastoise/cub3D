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
#define SCALE 16
#define ENTER 36
#define ESC 53
#define W 13
#define A 0
#define S 1
#define D 2
#define L 123
#define R 124
#define UP 126
#define DOWN 125

typedef struct  s_params
{
    int         settings;
    int         width;
    int         height;
    int         t;
    int         r;
    int         g;
    int         b;
    int         floor_color;
    int         ceilling_color;
    char        *north_texture;
    char        *south_texture;
    char        *west_texture;
    char        *east_texture;
    char        *sprite_texture;
    int         fd;
    char        **map;
    int         map_height;
    int         map_width;
    int         map_start;
    int         plr_found;
    int         error;
    double      wall_height;
    char        dir_h;
    char        dir_v;
    int		    hit_x;
    int		    hit_y;
}               t_params;

typedef struct s_image
{
    int         texture_width;
    int         texture_height;
    void        *texture_img;
    char        *texture_addr;
    int         texture_bpp;
    int         texture_line_length;
    int         texture_endian;
    char        *texture_path;
}               t_image;

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

typedef struct  s_all
{
    t_params    *params;
    t_data      *data;
    t_player    *plr;
    t_image     text[5];
}               t_all;

void    draw_floor_and_ceiling(t_all *all);
// void    params_init(t_params *params);
// void    define_resolution(char *line, t_params *params);
int     create_trgb(int r, int g, int b);
// int     define_color(char *line, t_params *params);
void    parser(char *line, t_all *all);
void    init_player(t_all *all);
// void    draw_player(t_all *all);
// void	ft_cast_ray(t_all *all);
// char    **create_map(t_list **head, int size);
void    read_map(char *argv1, t_all *all);
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
// void    scale_map(t_data  *data, int x, int y, int color);
void    draw_map(t_all *all);
void	ft_cast_rays(t_all *all);
// int     key_press(int key, t_all *all);
void    check_map(t_all *all);
// int     check_wall(int key, t_all *all);
void    error_close(t_params *params);
// void    check_arg_name(char *argv1, t_params *params);
// void    check_player(t_all *all, char *line);
void    make_rectangle_map(t_all *all);
void    cast_rays(t_all *all);
void    draw_wall(t_all *all, char side);
void	buff_textures(t_all *all);
// int    pixel_take(t_all *all, int x, int y, int color);
int    pixel_take(t_all *all, int x, int y, char side, double step);


#endif