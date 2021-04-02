/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 17:05:28 by eblastoi          #+#    #+#             */
/*   Updated: 2021/03/27 17:05:30 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
                plr->x = (double)x + 0.5;
                plr->y = (double)y + 0.5;
                if (map[y][x] == 'N')
                    plr->direction = 3 * M_PI_2;
                else if (map[y][x] == 'E')
                    plr->direction =  2 * M_PI;
                else if (map[y][x] == 'W')
                    plr->direction = M_PI;
                else if (map[y][x] == 'S')
                    plr->direction = M_PI_2;
                break ;
            }
            x++;
        }
        y++;
    }
}

void    draw_player(t_all *all)
{
    double x;
    double y;
    double x_end;
    double y_end;

    x = all->plr->x * SCALE;
    y = all->plr->y * SCALE;
    x_end = (all->plr->x + 1) * SCALE;
    y_end = (all->plr->y + 1) * SCALE;
    while (y < y_end && all->map[(int)y / SCALE][(int)x / SCALE] != '1') 
    {
        while (x < x_end && all->map[(int)y / SCALE][(int)x / SCALE] != '1')
            my_mlx_pixel_put(all->data, x++, y, 0x00FF00);
        x -= SCALE;
        y++;
    }
    // scale_map(all->data, all->plr->x, all->plr->y, 0x00FF00);
}