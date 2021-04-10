/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:47:37 by eblastoi          #+#    #+#             */
/*   Updated: 2021/04/10 16:47:40 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_cast_ray(t_all *all)
{
    double  ray_x;
    double  ray_y;

    ray_x = all->plr->x * SCALE + SCALE/2;
    ray_y = all->plr->y * SCALE + SCALE/2;
	while (all->params->map[(int)(ray_y / SCALE)][(int)(ray_x / SCALE)] != '1')
	{
		ray_x += cos(all->plr->direction);
		ray_y += sin(all->plr->direction);
        my_mlx_pixel_put(all->data, ray_x, ray_y, 0x990099);
	    
	}
}

void	ft_cast_rays(t_all *all)
{
	t_player	ray;
	double      start; 
    double      end; 

    ray = *all->plr; // задаем координаты и направление луча равные координатам игрока
    start = ray.direction - M_PI_4; // начало веера лучей
    end = ray.direction + M_PI_4; // край веера лучей
  while (start <= end)
	{
		ray.x = all->plr->x * SCALE + SCALE/2; // каждый раз возвращаемся в точку начала
		ray.y = all->plr->y * SCALE + SCALE/2;
		while (all->params->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
		{
			ray.x += cos(start);
			ray.y += sin(start);
			my_mlx_pixel_put(all->data, ray.x, ray.y, 0x990099);
		}
	    start += M_PI_2 / 100; //[угол обзора] / [количество лучей];
	}
}

// int     search_cross(t_all *all, double x, double y)
// {
//     x = (int)x / SCALE;
//     y = (int)y / SCALE;
//     if (all->params->map[(int)y][(int)x] == ' ')
//         return (-1);
//     else if (all->params->map[(int)y][(int)x] == '1')
//         return (1);
//     else
//         return (0);
// }

// double  horizont_cross(t_all *all)
// {
//     double  x;
//     double  y;
//     double  step_x;
//     double  step_y;
//     int     cross_status;

//     step_y = SCALE;
//     step_x = SCALE / tan(all->plr->direction);
//     if (all->plr->direction > 270 && all->plr->direction < 360)
//     {
//         y = (int)all->plr->y / 40 * 40 - 0.01;
//         step_y = -step_y;
//     }
//     else
//     {
//         y = (int)all->plr->y / 40 * 40 + 40;
//         step_x = -step_x;
//     }
//     x = all->plr->x + (all->plr->y - y) / tan(all->plr->direction);
//     while ((cross_status = search_cross(all, x, y)) == 0)
//     {
//         x += step_x;
//         y += step_y;
//     }
//     // if (cross_status == -1)
//     //     return (10000000);
//     return (); //формула нахождения расстояния между двух точек
// }

// double  vertical_cross(t_all *all)
// {

// }

// void    cast_rays(t_all *all)
// {
//     double  start;
//     double  end;
//     double  step;
//     double  dist_h;
//     double  dist_v;
//     int     i;

//     start = all->plr->direction - M_PI_4; // 45 град
//     end = all->plr->direction + M_PI_4;
//     i = 0;
//     while (start > end)
//     {
//         dist_h = horizont_crosst(all);
//         dist_v = vertical_cross(all);
//         if (dist_h < dist_v)
//             draw_wall();
//         else
//             dra_wall();
//         start -= step;
//         i++;
//     }
// }
