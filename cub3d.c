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
        // draw_floor_and_ceiling(all);
        cast_rays(all);
        draw_map(all);
        ft_cast_rays(all);
        draw_sprites(all);
        mlx_put_image_to_window(all->data->mlx, all->data->win, all->data->img, 0, 0);
    }
    return (0);
}

void    start_cub(t_all *all)
{
    init_player(all);
    sprites_init(all);
    all->data->mlx = mlx_init();
    all->data->win = mlx_new_window(all->data->mlx, all->params->width, all->params->height, "cub3D");
    all->data->img = mlx_new_image(all->data->mlx, all->params->width, all->params->height);
    all->data->addr = mlx_get_data_addr(all->data->img, &all->data->bits_per_pixel, &all->data->line_length, &all->data->endian);
    buff_textures(all);
    // draw_player(&all);
    // ft_cast_ray(&all);
    cast_rays(all);
    draw_map(all);
    ft_cast_rays(all);
    draw_sprites(all);
    mlx_put_image_to_window(all->data->mlx, all->data->win, all->data->img, 0, 0);
    // mlx_put_image_to_window(data.mlx, data.win, all.text[1].texture_img, 0, 0);
    mlx_hook(all->data->win, 2, 1L<<0, key_press, all);
    mlx_hook(all->data->win, 17, 1L<<0, exit_cub, all);
    // mlx_loop_hook(data.mlx, key_press, &all);
    mlx_loop(all->data->mlx);
}

void     check_arg_name(char **argv, t_all *all)
{
    char    *str;
    char    **name;

    str = "cub";
    name = ft_split(argv[1], '.');
    if ((ft_strcmp(name[1], str) != 0))
    {
        all->params->error = 1;
        error_close(all);
    }
    if (argv[2])
    {
        if (ft_strcmp(argv[2], "--save") != 0)
        { 
            printf("Invalid argument\n");
            start_cub(all);
        }
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
        check_arg_name(argv, &all);
        read_map(argv[1], &all);
        start_cub(&all);
    }
    else if (argc == 3)
    {
        check_arg_name(argv, &all);
        read_map(argv[1], &all);
        init_player(&all);
        sprites_init(&all);
        data.mlx = mlx_init();
        data.img = mlx_new_image(data.mlx, params.width, params.height);
        data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
        buff_textures(&all);
        cast_rays(&all);
        draw_map(&all);
        ft_cast_rays(&all);
        draw_sprites(&all);
        create_bmp(&all);
    }
    else if (argc < 2)
        printf("Need a map");
    return (0);
}