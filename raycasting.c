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
	all->params->dir_h = 0;
	all->params->dir_v = 0;
	if (sin(angle) < 0)
	{
		all->params->dir_h = 0; //'N'
		delta_y = -1;
		new_y = (int)all->plr->y;
	}
	else if (sin(angle) >= 0)
	{
		all->params->dir_h = 1; //'S'
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
	}
	if (sin(angle) >= 0)
		all->params->hit_x = 1 - (new_x - (int)new_x);
	else
		all->params->hit_x = new_x - (int)new_x;
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
		all->params->dir_v = 2; //'E'
		delta_x = 1;
		new_x = (int)all->plr->x + 1; 
	}
	else if (cos(angle) < 0)
	{
		all->params->dir_v = 3; //'W'
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
	}
	if (cos(angle) < 0)
		all->params->hit_y = 1 - (new_y - (int)new_y);
	else
		all->params->hit_y = new_y - (int)new_y;
    return (fabs(ray_len));
}


void    cast_rays(t_all *all)
{
    double  start;
    //double  end;
    double  step; 
    double  dist_h;
    double  dist_v;
    int     i;

	double asp = all->params->width / (double)all->params->height;

    //start = all->plr->direction - M_PI * asp / 6; // -30град FOV 60 град
    //end = all->plr->direction + M_PI * asp / 6; // +30град 
	step = M_PI / 3 / (double)all->params->width;
    i = 0;
	all->params->dist_to_wall = (double*)malloc(sizeof(double) * all->params->width + 1);
    //while (start < end)
	while(i < all->params->width)
    {
		start = all->plr->direction - M_PI / 6 + i * step;
        dist_h = horizont_cross(all, start) * cos(start - all->plr->direction);
        dist_v = vertical_cross(all, start) * cos(start - all->plr->direction);
        if (dist_h < dist_v)
		{
			all->params->hit = all->params->hit_x;
			all->params->wall_height = (all->params->height / dist_h) * asp;
			all->params->dist_to_wall[i] = dist_h;
			// printf("dist_h = %lf\n", all->params->dist_to_wall[i]);
			draw(all, i, all->params->dir_h);
		}
        else
		{
			all->params->hit = all->params->hit_y;
			all->params->wall_height = (all->params->height / dist_v) * asp;
			all->params->dist_to_wall[i] = dist_v;
			// printf("dist_v = %lf\n", all->params->dist_to_wall[i]);
			draw(all, i, all->params->dir_v);
		}
        //start += step;
        i++;
    }
}