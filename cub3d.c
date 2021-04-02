/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 17:00:25 by eblastoi          #+#    #+#             */
/*   Updated: 2021/03/27 17:00:35 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    check_wall(int key, t_all *all)
{
    double  new_x;
    double  new_y;

    new_y = all->plr->y;
    new_x = all->plr->x;
    if (key == W || key == UP)
    {
        new_y += sin(all->plr->direction);
        new_x += cos(all->plr->direction);
    }
    if (key == S || key == DOWN)
    {
        new_y -= sin(all->plr->direction);
        new_x -= cos(all->plr->direction);
    }
    if (key == L)
        all->plr->direction -= 0.1;
    if (key == R)
        all->plr->direction += 0.1;
    if (key == A)
    {
        new_x += sin(all->plr->direction + 2 * M_PI);
        new_y -= cos(all->plr->direction + 2 * M_PI);
    }
    if (key == D)
    {
        new_x += sin(all->plr->direction + M_PI);
        new_y -= cos(all->plr->direction + M_PI);
    }
    if (all->map[(int)new_y / SCALE][(int)new_x / SCALE] != '1')
    {
        all->plr->x = new_x;
        all->plr->y = new_y;
        return (0);
    }
    return (1);
}

int     exit_cub(t_all *all)
{
    (void)all;
    //free malloc, close fd
    exit(0);
}

int    key_press(int key, t_all *all)
{
    if (key == ESC)
    {
        //free malloc, close fd
        exit_cub(all);
    }
    if ((check_wall(key, all)) == 0)
    {
        draw_map(all);
        // draw_player(all);
        // ft_cast_ray(all);
        ft_cast_rays(all);
        mlx_put_image_to_window(all->data->mlx, all->data->win, all->data->img, 0, 0);
    }
    return (0);
}

void    draw_floor_and_ceiling(t_all *all)
{
    int x;
    int y;

    y = 0;
    while (y < all->params->height / 2)
    {
        x = 0;
        while (x < all->params->width)
        {
            my_mlx_pixel_put(all->data, x, y, all->params->ceilling_color);
            x++;
        }
        y++;
    }
    y = all->params->height / 2;
    while (y < all->params->height)
    {
        x = 0;
        while (x < all->params->width)
        {
            my_mlx_pixel_put(all->data, x, y, all->params->floor_color);
            x++;
        }
        y++;
    }
}

void error_close(int fd)
{
    //free all
    close (fd);
    exit (1);
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
    all.params = &params;
    draw_floor_and_ceiling(&all);
    draw_map(&all);
    // draw_player(&all);
    // ft_cast_ray(&all);
    // ft_cast_rays(&all);
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_hook(data.win, 2, 1L<<0, key_press, &all);
    mlx_hook(data.win, 17, 1L<<0, exit_cub, &all);
    // mlx_loop_hook(data.mlx, key_press, &all);
    mlx_loop(data.mlx);
    // else if (argc == 3)
    // {
        
    // }
    return (0);
}