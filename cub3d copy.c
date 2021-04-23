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
        new_y += 0.3 * sin(all->plr->direction);
        new_x += 0.3 * cos(all->plr->direction);
    }
    if (key == S || key == DOWN)
    {
        new_y -= 0.3 * sin(all->plr->direction);
        new_x -= 0.3 * cos(all->plr->direction);
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
        new_x += 0.3 * sin(all->plr->direction + M_PI);
        new_y -= 0.3 * cos(all->plr->direction + M_PI);
    }
    if ((new_x < all->params->map_width) && (new_y < all->params->map_height))
    {
        if (all->params->map[(int)new_y][(int)new_x] != '1')
        {
            all->plr->x = new_x;
            all->plr->y = new_y;
            return (0);
        }
    }
    return (1);
}

int     exit_cub(t_all *all)
{
    //free malloc, close fd
    close (all->params->fd);
    free (all->params->map);
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
        // draw_player(all);
        // ft_cast_ray(all);
        cast_rays(all);
        draw_map(all);
        ft_cast_rays(all);
        mlx_put_image_to_window(all->data->mlx, all->data->win, all->data->img, 0, 0);
    }
    return (0);
}

int    pixel_take(t_all *all, int x, int y, char side, double step)
{
    char    *dst;
    double  text_y;
    int     color;
    
    text_y = (y + all->params->hit_x) * step;
    dst = NULL;
    if (side == 'N')
        dst = all->text[0].texture_addr + ((int)text_y * all->text[0].texture_line_length + x * (all->text[0].texture_bpp / 8));
    else if (side == 'S')
        dst = all->text[1].texture_addr + ((int)text_y * all->text[1].texture_line_length + x * (all->text[1].texture_bpp / 8));
    else if (side == 'E')
        dst = all->text[2].texture_addr + ((int)text_y * all->text[2].texture_line_length + x * (all->text[2].texture_bpp / 8));
    else if (side == 'W')
        dst = all->text[3].texture_addr + ((int)text_y * all->text[3].texture_line_length + x * (all->text[3].texture_bpp / 8));
    *(unsigned int*)dst = color;
    return (color);
}

void    draw_wall(t_all *all, char side)
{
    int     z;
    int     x;
    int     y;
    double  y_offset;
    double  step;
    int     color;

    x = 0;
    y = 0;
    step = 0;
    color = 0;
    y_offset = 0;

    z = all->params->width * (-0.5);
    while (z < all->params->width * 0.5)
    {
        if (all->params->wall_height > all->params->height)
        {
            y_offset = (all->params->wall_height - all->params->height) / 2;
            all->params->wall_height = all->params->height;
        }
        if (y_offset > 0)
            y = step * y_offset;
        color = pixel_take(all, x, y, side, step);
        while (y < all->params->wall_height)
        {
            x = 0;
            while (x < 1)
            {
                if (all->params->dir_h == 'N')
                {
                    // n = all->text[0].texture_height / all->params->wall_height;
                    my_mlx_pixel_put(all->data, x, y, color);
                }
                else
                    my_mlx_pixel_put(all->data, x, y, 0xFF5533);
                x++;
            }
            y++;
        }
        z++;
    }

    
    // x = (int)(all->params->hit_x * all->text[0].texture_width);
    
    
    // step = (double)all->text[0].texture_height / all->params->wall_height;
    // y = screen_y - (all->params->height - all->params->wall_height) / 2;
    // color = *((int *)(all->text[0].texture_addr + (y * all->text[0].texture_line_length + screen_x * (all->text[0].texture_bpp / 8))));
    
    // if (all->params->dir_h == 'N' && side == 'h')
    // {
    //     // n = all->text[0].texture_height / all->params->wall_height;
    //     my_mlx_pixel_put(all->data, x, y, color);
    // }
    // else
    //     my_mlx_pixel_put(all->data, screen_x, screen_y, 0xFF5533);
}

void    draw_floor_and_ceiling(t_all *all)
{
    int x;
    int y;

    y = 0;
    while (y < all->params->height)
    {
        x = 0;
        while (x < all->params->width)
        {
            if (y < (all->params->height - all->params->wall_height) / 2)
                my_mlx_pixel_put(all->data, x, y, all->params->ceilling_color);
        // else if ((y >= (all->params->height - all->params->wall_height) / 2) && (y < (all->params->height + all->params->wall_height) / 2))
        //     // my_mlx_pixel_put(all->data, x, y, 0xFF5533);
        //     draw_wall(all, x, y, side);
            else if ((y >= (all->params->height + all->params->wall_height) / 2) && (y < all->params->height - 1))
                my_mlx_pixel_put(all->data, x, y, all->params->floor_color);
            x++;
        }
        y++;
    }
}

void error_close(t_params *params)
{
    if (params->error == 1)
        printf("Error\nInvalid file name\n");
    else if (params->error == 2)
         printf("Error\nInvalid parameter");
    else if (params->error == 3)
        printf("Error\nIncorrect number of parameters");
    else if (params->error == 4)
        printf("Error\nThere must be one player on the map");
    else if (params->error == 5)
       printf("Error\nNot valid map\n");
    else if (params->error == 6)
        printf("Error\nResolution must have two int value");
    else if (params->error == 7)
        printf("Error\nColors must have three int value");
    else if (params->error == 8)
        printf("Error\nColors must be in range [0,255]");
    else if (params->error == 9)
        printf("Error\nSpaces in the map");
    // free all malloc
    close (params->fd);
    free (params->map);
    exit (1);
}

void     check_arg_name(char *argv1, t_params *params)
{
    char    *str;
    char    **name;

    str = "cub";
    name = ft_split(argv1, '.');
    if ((ft_strcmp(name[1], str) != 0))
    {
        params->error = 1;
        error_close(params);
    }
}

int     main(int argc, char **argv)
{
    t_params    params;
    t_data      data;
    t_player    plr;
    t_all       all;

    all.plr = &plr;
    all.data = &data;
    all.params = &params;
    if (argc == 2)
    {
        check_arg_name(argv[1], &params);
        read_map(argv[1], &all);
    }
    else
        printf("Need a map");
    init_player(&all);
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, params.width, params.height, "cub3D");
    data.img = mlx_new_image(data.mlx, params.width, params.height);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    draw_floor_and_ceiling(&all);
    // draw_player(&all);
    // ft_cast_ray(&all);
    buff_textures(&all);
    cast_rays(&all);
    draw_map(&all);
    ft_cast_rays(&all);
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    // mlx_put_image_to_window(data.mlx, data.win, all.text[1].texture_img, 0, 0);
    mlx_hook(data.win, 2, 1L<<0, key_press, &all);
    mlx_hook(data.win, 17, 1L<<0, exit_cub, &all);
    // mlx_loop_hook(data.mlx, key_press, &all);
    mlx_loop(data.mlx);
    // else if (argc == 3)
    // {
        
    // }
    return (0);
}