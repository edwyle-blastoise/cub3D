/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:18:33 by eblastoi          #+#    #+#             */
/*   Updated: 2021/03/11 15:18:36 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include "minilibx_opengl/mlx.h"
#define SCALE 16

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

void            params_init(t_params *params)
{
    params->width = 0;
    params->height = 0;
    params->t = 0;
    params->r = 0;
    params->g = 0;
    params->b = 0;
    params->floor_color = 0;
    params->ceilling_color = 0;
    params->map = NULL;
}

void    define_resolution(char *line, t_params *params)
{
    char    **resolution;

    resolution = NULL;
    resolution = ft_split(line, ' ');
    params->width = ft_atoi(resolution[1]);
    params->height = ft_atoi(resolution[2]);
    printf("%d %d\n", params->width, params->height);
}

int    create_trgb(int r, int g, int b)
{
    int t;

    t = 0;
    return (t << 24 | r << 16 | g << 8 | b);
}

int    define_color(char *line, t_params *params)
{
    char        **floor_color;
    char        **rgb;
    int         color;

    floor_color = NULL;
    rgb = NULL;
    color = 0;
    floor_color = ft_split(line, ' ');
    rgb = ft_split(floor_color[1], ',');
    params->r = ft_atoi(rgb[0]);
    params->g = ft_atoi(rgb[1]);
    params->b = ft_atoi(rgb[2]);
    if ((params->r >= 0 && params->r <= 255) && (params->g >= 0 && params->g <= 255) \
        && (params->b >= 0 && params->b <= 255))
        {
            color = create_trgb(params->r, params->g, params->b);
            return (color);
        }
    else
        printf("Error\nColors must be in range [0,255]");
    return (0);
}

void    parser(char *line, t_params *params)
{
    int i;
    
    i = 0;
    while (line[i])
    {
        if (line[i] == 'R' && line[++i] == ' ') //resolution;
        {
            printf("R ");
            define_resolution(line, params);
        }
        else if (line[i] == 'N' && line[++i] == 'O' && line[++i] == ' ')  //north_texture;
        {
            printf("NO\n");
        }
        else if (line[i] == 'S' && line[++i] == 'O' && line[++i] == ' ') //south_texture;
        {
            printf("SO\n");
        }
        else if (line[i] == 'W' && line[++i] == 'E' && line[++i] == ' ') //west_texture;
        {
            printf("WE\n");
        }
        else if (line[i] == 'E' && line[++i] == 'A' && line[++i] == ' ') //east_texture;
        {
            printf("EA\n");
        }
        else if (line[i] == 'S' && line[++i] == ' ') //sprite_texture;
        {
            printf("S\n");
        }
        else if (line[i] == 'F' && line[++i] == ' ') //floor_color;
        {
            params->floor_color = define_color(line, params);
            printf("F_color: %d\n", params->floor_color);
        }
        else if (line[i] == 'C' && line[++i] == ' ') //ceilling_color;
        {
            params->ceilling_color = define_color(line, params);
            printf("C_color: %d\n", params->ceilling_color);
        }
        // else if (line[i] == '\0')
        else
            return ;
    }
}

char    **create_map(t_list **head, int size)
{
    int     i;
    t_list *tmp;
    char    **map;
    
    i = 0;
    tmp = *head;
    map = ft_calloc(sizeof(char*), size + 1);
    while (tmp)
    {
        map[i] = ft_strdup(tmp->content);
        i++;
        tmp = tmp->next;
    }
    i = 0;
    ft_lstclear(head, &free);
    while (map[i])
    {
        ft_putendl_fd(map[i], 1);
        i++;
    }
    return (map);
}

char         **read_map(char *argv1)
{
    int         fd;
    char        *line;
    t_list      *head;
    t_params    params;
    
    line = NULL;
    head = NULL;
    fd = open(argv1, O_RDONLY);
    params_init(&params);
    while (get_next_line(fd, &line) > 0)
    {
        if (*line == ' ' || *line == '1')
            ft_lstadd_back(&head, ft_lstnew(line));
        parser(line, &params);
    }
    ft_lstadd_back(&head, ft_lstnew(line));
    return (create_map(&head, ft_lstsize(head)));
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void            scale_map(t_data  *data, t_point point)
{
    t_point end;

    end.x = (point.x + 1) * SCALE;
    end.y = (point.y + 1) * SCALE;
    point.x *= SCALE;
    point.y *= SCALE;
    while (point.y < end.y)
    {
        while (point.x < end.x)
            my_mlx_pixel_put(data, point.x++, point.y, 0xFFFFFF);
        point.x -= SCALE;
        point.y++;
    }
}

void      draw_map(t_params *params, t_data  *data)
{
    t_point point;

    point.x = 0;
    point.y = 0;
    while (params->map[point.y])
    {
        point.x = 0;
         while (params->map[point.y][point.x])
        {
            if (params->map[point.y][point.x] == '1')
                // my_mlx_pixel_put(data, point.x, point.y, 0xFFFFFF);
                scale_map(data, point);
            point.x++;
        }
        point.y++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_loop(data->mlx);
}

int         main(int argc, char **argv)
{
    t_params    params;
    t_data      data;
    
    if (argc == 2)
        params.map = read_map(argv[1]);
    else
        printf("Need a map");
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
    data.img = mlx_new_image(data.mlx, 1920, 1080);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    draw_map(&params, &data);
    // else if (argc == 3)
    // {
        
    // }
    return (0);
}
