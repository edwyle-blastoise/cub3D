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
    start = ray.direction - M_PI_4; // начало веера лучей (-45град)
    end = ray.direction + M_PI_4; // край веера лучей (+45град)
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

double  horizont_cross(t_all *all)
{
    double  new_x;
    double  new_y;
    int  	delta_x;
    int  	delta_y;
	double	ray_len;

	new_x = 0;
	new_y = 0;
	ray_len = INFINITY;
	if (sin(all->plr->direction) == 0)
		return (ray_len);
	else if (sin(all->plr->direction) < 0)
	{
		delta_y = -1;
		new_y = (int)all->plr->y;
	}
	else if (sin(all->plr->direction) > 0)
	{
		delta_y = 1;
		new_y = (int)all->plr->y + 1;
	}
	delta_x = 1 / tan(all->plr->direction);
	new_x = all->plr->x + (new_y - all->plr->y) * delta_x;
	while (new_y > 0 && new_y < all->params->strings)
	{
		if (new_x < 0 || new_x >= all->params->string_len)
			break ;
		if (all->params->map[(int)new_y - (delta_y == -1 ? 1 : 0)][(int)new_x] == '1')
		{
			ray_len = (new_y - all->plr->y) / sin(all->plr->direction);
			break ;
		}
		new_y += delta_y;
		new_x += delta_x * delta_y;
	}
	// printf("horizont_cross: new_y %lf, new_x %lf\n", new_y, new_x);
    return (ray_len);
}

double  vertical_cross(t_all *all)
{
	double  new_x;
    double  new_y;
    int  	delta_x;
    int  	delta_y;
	double	ray_len;

	new_x = 0;
	new_y = 0;
	ray_len = INFINITY;
	if (cos(all->plr->direction) == 0)
		return (ray_len);
	else if (cos(all->plr->direction) > 0)
	{
		delta_x = 1;
		new_x = (int)all->plr->x + 1; 
	}
	else if (cos(all->plr->direction) < 0)
	{
		delta_x = -1;
		new_x = (int)all->plr->x;
	}
	delta_y = tan(all->plr->direction);
	new_y = all->plr->y + (new_x - all->plr->x) * delta_y;
	while (new_x > 0 && new_x < all->params->string_len)
	{
		if (new_y < 0 || new_y >= all->params->strings)
			break ;
		if (all->params->map[(int)new_y][(int)new_x - (delta_x == -1 ? 1 : 0)] == '1')
		{
			ray_len = (new_x - all->plr->x) / cos(all->plr->direction);
			break ;
		}
		new_y += delta_x * delta_y;
		new_x += delta_x;
	}
	printf("vertical_cross: new_y %lf, new_x %lf\n", new_y, new_x);
	printf("Angle: %lf\n", all->plr->direction);
    return (ray_len);
}

void    cast_rays(t_all *all)
{
	horizont_cross(all);
    vertical_cross(all);
    // double  start;
    // double  end;
    // double  step;
    // double  dist_h;
    // double  dist_v;
    // int     i;

    // start = all->plr->direction - M_PI_4; // 45 град
    // end = all->plr->direction + M_PI_4;
    // i = 0;
    // while (start > end)
    // {
    //     dist_h = horizont_cross(all);
    //     dist_v = vertical_cross(all);
    //     if (dist_h < dist_v)
    //         draw_wall(all);
    //     else
    //         dra_wall();
    //     start -= step;
    //     i++;
    // }
	// mlx_put_image_to_window(all->data->mlx, all->data->win, all->data->img, 0, 0);
}

// void	draw_wall(t_all *all)
// {

// }