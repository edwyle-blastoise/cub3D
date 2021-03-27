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
                plr->x = (double)x;
                plr->y = (double)y;
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

void	ft_cast_ray(t_all *all)
{
    double  ray_x;
    double  ray_y;

    ray_x = all->plr->x * SCALE + SCALE/2;
    ray_y = all->plr->y * SCALE + SCALE/2;
	while (all->map[(int)(ray_y / SCALE)][(int)(ray_x / SCALE)] != '1')
	{
		ray_x += cos(all->plr->direction);
		ray_y += sin(all->plr->direction);
        my_mlx_pixel_put(all->data, ray_x, ray_y, 0x990099);
	    
	}
}

void	ft_cast_rays(t_all *all)
{
	t_player	ray;
	double start; 
    double end; 

    ray = *all->plr; // задаем координаты и направление луча равные координатам игрока
    start = ray.direction - M_PI_4; // начало веера лучей
    end = ray.direction + M_PI_4; // край веера лучей
  while (start <= end)
	{
		ray.x = all->plr->x * SCALE + SCALE/2; // каждый раз возвращаемся в точку начала
		ray.y = all->plr->y * SCALE + SCALE/2;
		while (all->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
		{
			ray.x += cos(start);
			ray.y += sin(start);
			my_mlx_pixel_put(all->data, ray.x, ray.y, 0x990099);
		}
	    start += M_PI_2 / 40; //[угол обзора] / [количество лучей];
	}
}