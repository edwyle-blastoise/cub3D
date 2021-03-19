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

#include "cub3d.h"

void    params_init(t_params *params)
{
    params->width = 0;
    params->height = 0;
    params->t = 0;
    params->r = 0;
    params->g = 0;
    params->b = 0;
    params->floor_color = 0;
    params->ceilling_color = 0;
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

int     create_trgb(int r, int g, int b)
{
    int t;

    t = 0;
    return (t << 24 | r << 16 | g << 8 | b);
}

int     define_color(char *line, t_params *params)
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

char    **read_map(char *argv1, t_params *params)
{
    int         fd;
    char        *line;
    t_list      *head;
    
    line = NULL;
    head = NULL;
    fd = open(argv1, O_RDONLY);
    params_init(params);
    while (get_next_line(fd, &line) > 0)
    {
        if (*line == ' ' || *line == '1')
            ft_lstadd_back(&head, ft_lstnew(line));
        parser(line, params);
    }
    ft_lstadd_back(&head, ft_lstnew(line));
    return (create_map(&head, ft_lstsize(head)));
}

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    scale_map(t_data  *data, int x, int y, int color)
{
    int x_end;
    int y_end;

    x_end = (x + 1) * SCALE;
    y_end = (y + 1) * SCALE;
    x *= SCALE;
    y *= SCALE;
    while (y < y_end)
    {
        while (x < x_end)
            my_mlx_pixel_put(data, x++, y, color);
        x -= SCALE;
        y++;
    }
}

void    init_player(char **map, t_player *plr)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (ft_strchr("NEWS", map[y][x]))
            {
                plr->x = (double)x;
                plr->y = (double)y;
                plr->direction = M_PI;
                break ;
            }
            x++;
        }
        y++;
    }
}

void    draw_player(t_all *all)
{
    my_mlx_pixel_put(all->data, all->plr->x * SCALE, all->plr->y * SCALE, 0x00FF00);
}

void    draw_map(t_all *all)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (all->map[y])
    {
        x = 0;
         while (all->map[y][x])
        {
            if (all->map[y][x] == '1')
                scale_map(all->data, x, y, 0xFFFFFF);
            else
                scale_map(all->data, x, y, 0x000000);
            x++;
        }
        y++;
    }
}

int    key_press(int key, t_all *all)
{
    if (key == W)
    {
        all->plr->y -= 1;
    }
    if (key == A)
        all->plr->x -= 1;
    if (key == S)
        all->plr->y += 1;
    if (key == D)
        all->plr->x += 1;
    else if (key == ESC)
    {
        //free malloc, close fd
        exit (0);
    }
    draw_map(all);
    draw_player(all);
    mlx_put_image_to_window(all->data->mlx, all->data->win, all->data->img, 0, 0);
    return (0);
}

int     main(int argc, char **argv)
{
    t_params    params;
    t_data      data;
    t_player    plr;
    t_all       all;
    
    if (argc == 2)
        all.map = read_map(argv[1], &params);
    else
        printf("Need a map");
    init_player(all.map, &plr);
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, params.width, params.height, "Hello world!");
    data.img = mlx_new_image(data.mlx, params.width, params.height);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    all.plr = &plr;
    all.data = &data;
    draw_map(&all);
    draw_player(&all);
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_hook(data.win, 2, 1L<<0, key_press, &all);
    mlx_loop(data.mlx);
    // else if (argc == 3)
    // {
        
    // }
    return (0);
}
