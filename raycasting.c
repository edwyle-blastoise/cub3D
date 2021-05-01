#include "cub3d.h"

void	ft_cast_rays(t_all *all)
{
	t_player	ray;
	double		start;
	double		end;
	int			x;

	ray = *all->plr;
	start = ray.direction - M_PI / 6;
	end = ray.direction + M_PI / 6;
	x = 0;
	while (start <= end)
	{
		ray.x = all->plr->x * SCALE;
		ray.y = all->plr->y * SCALE;
		while (all->params->map[(int)(ray.y) \
			/ SCALE][(int)(ray.x) / SCALE] != '1')
		{
			ray.x += cos(start);
			ray.y += sin(start);
			my_mlx_pixel_put(all->data, ray.x, ray.y, 0x990099);
		}
		start += M_PI / 3 / all->params->width;
		x++;
	}
}

double	horizont_cross(t_all *all, double angle)
{
	double	new_x;
	double	new_y;
	int		delta_x;
	int		delta_y;
	double	ray_len;

	new_x = 0;
	new_y = 0;
	ray_len = INFINITY;
	all->params->dir_h = 0;
	all->params->dir_v = 0;
	if (sin(angle) < 0)
	{
		all->params->dir_h = 0;
		delta_y = -1;
		new_y = (int)all->plr->y;
	}
	else if (sin(angle) >= 0)
	{
		all->params->dir_h = 1;
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

double	vertical_cross(t_all *all, double angle)
{
	double	new_x;
	double	new_y;
	int		delta_x;
	int		delta_y;
	double	ray_len;

	new_x = 0;
	new_y = 0;
	ray_len = INFINITY;
	if (cos(angle) >= 0)
	{
		all->params->dir_v = 2;
		delta_x = 1;
		new_x = (int)all->plr->x + 1;
	}
	else if (cos(angle) < 0)
	{
		all->params->dir_v = 3;
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

void	cast_rays(t_all *all)
{
	double	start;
	double	step;
	double	dist_h;
	double	dist_v;
	int		i;

	start = all->plr->direction - M_PI / 6;
	step = M_PI / 3 / (double)all->params->width;
	i = 0;
	while (i < all->params->width)
	{
		start = all->plr->direction - M_PI / 6 + i * step;
		dist_h = horizont_cross(all, start) * cos(start - all->plr->direction);
		dist_v = vertical_cross(all, start) * cos(start - all->plr->direction);
		if (dist_h < dist_v)
		{
			all->params->hit = all->params->hit_x;
			all->params->wall_height = (all->params->height / dist_h);
			all->params->dist_to_wall[i] = dist_h;
			draw(all, i, all->params->dir_h);
		}
		else
		{
			all->params->hit = all->params->hit_y;
			all->params->wall_height = (all->params->height / dist_v);
			all->params->dist_to_wall[i] = dist_v;
			draw(all, i, all->params->dir_v);
		}
		i++;
	}
}
