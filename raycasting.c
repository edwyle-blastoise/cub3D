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
	int			x;

    ray = *all->plr; // задаем координаты и направление луча равные координатам игрока
    start = ray.direction - M_PI / 6; // начало веера лучей (-30град)
    end = ray.direction + M_PI / 6; // край веера лучей (+30град)
	x = 0;
  	while (start <= end)
	{
		ray.x = all->plr->x * SCALE; // каждый раз возвращаемся в точку начала
		ray.y = all->plr->y * SCALE;
		while (all->params->map[(int)(ray.y) / SCALE][(int)(ray.x) / SCALE] != '1')
		{
			ray.x += cos(start);
			ray.y += sin(start);
			my_mlx_pixel_put(all->data, ray.x, ray.y, 0x990099);
		}
		// all->params->len_ray = hypotf(ray.x - all->plr->x, ray.y - all->plr->y) * cosf(start - all->plr->direction);
		// all->params->wall_height = (all->params->height / all->params->len_ray);
		// draw_cub(all, x);
	    start += M_PI / 3 / all->params->width; //[угол обзора] / [количество лучей];
		x++;
	}
}

double  horizont_cross(t_all *all, double angle)
{
    double  new_x;
    double  new_y;
    int  	delta_x;
    int  	delta_y;
	double	ray_len;

	new_x = 0;
	new_y = 0;
	ray_len = INFINITY;
	if (sin(angle) < 0)
	{
		delta_y = -1;
		new_y = (int)all->plr->y;
	}
	else if (sin(angle) >= 0)
	{
		delta_y = 1;
		new_y = (int)all->plr->y + 1;
	}
	delta_x = 1 / tan(angle);
	new_x = all->plr->x + (new_y - all->plr->y) / sin(angle) * cos(angle);
	while (new_y > 0 && new_y < all->params->map_height)
	{
		if (new_x < 0 || new_x >= all->params->map_width)
			break ;
		if (all->params->map[(int)new_y - (delta_y == -1 ? 1 : 0)][(int)new_x] == '1')
		{
			ray_len = (new_y - all->plr->y) / sin(angle);
			break ;
		}
		new_y += delta_y;
		new_x += (delta_y / sin(angle)) * cos(angle);
		// printf("X %lf\n", new_x);
		// printf("Y %lf\n", new_y);
	}
    return (fabs(ray_len));
}

double  vertical_cross(t_all *all, double angle)
{
	double  new_x;
    double  new_y;
    int  	delta_x;
    int  	delta_y;
	double	ray_len;

	new_x = 0;
	new_y = 0;
	ray_len = INFINITY;
	if (cos(angle) >= 0)
	{
		delta_x = 1;
		new_x = (int)all->plr->x + 1; 
	}
	else if (cos(angle) < 0)
	{
		delta_x = -1;
		new_x = (int)all->plr->x;
	}
	delta_y = tan(angle);
	new_y = all->plr->y + (new_x - all->plr->x) / cos(angle) * sin(angle);
	while (new_x >= 0 && new_x < all->params->map_width)
	{
		if (new_y < 0 || new_y >= all->params->map_height)
			break ;
		if (all->params->map[(int)new_y][(int)new_x - (delta_x == -1 ? 1 : 0)] == '1')
		{
			ray_len = (new_x - all->plr->x) / cos(angle);
			break ;
		}
		new_y += (delta_x / cos(angle)) * sin(angle);
		new_x += delta_x;
		// printf("X_2 %lf\n", new_x);
		// printf("Y_2 %lf\n", new_y);
	}
    return (fabs(ray_len));
}

void    cast_rays(t_all *all)
{
    double  start;
    double  end;
    double  step;
    double  dist_h;
    double  dist_v;
    int     i;

    start = all->plr->direction - M_PI / 6; // -30град FOV 60 град
    end = all->plr->direction + M_PI / 6; // +30град 
	step = M_PI / 3 / all->params->width;
    i = 0;
    while (start < end)
    {
        dist_h = horizont_cross(all, start) * cos(start - all->plr->direction);
        dist_v = vertical_cross(all, start) * cos(start - all->plr->direction);
		printf("Ray_H: %lf\n", dist_h);
		printf("Ray_V: %lf\n\n", dist_v);
        if (dist_h < dist_v)
		{
			all->params->wall_height = (all->params->height / dist_h);
            draw_cub(all, i);
		}
        else
		{
			all->params->wall_height = (all->params->height / dist_v);
            draw_cub(all, i);
		}
        start += step;
        i++;
    }
	mlx_put_image_to_window(all->data->mlx, all->data->win, all->data->img, 0, 0);
}