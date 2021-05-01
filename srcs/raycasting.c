#include "cub3d.h"

double	count_ray_h(t_all *all, t_search_cross	*cross, double angle)
{
	double	ray_len;

	ray_len = INFINITY;
	while (cross->new_y > 0 && cross->new_y < all->params->map_height)
	{
		if (cross->new_x < 0 || cross->new_x >= all->params->map_width)
			break ;
		if (all->params->map[(int)cross->new_y - \
			(cross->delta_y == -1 ? 1 : 0)][(int)cross->new_x] == '1')
		{
			ray_len = (cross->new_y - all->plr->y) / sin(angle);
			break ;
		}
		cross->new_y += cross->delta_y;
		cross->new_x += (cross->delta_y / sin(angle)) * cos(angle);
	}
	if (sin(angle) >= 0)
		all->params->hit_x = 1 - (cross->new_x - (int)cross->new_x);
	else
		all->params->hit_x = cross->new_x - (int)cross->new_x;
	return (ray_len);
}

double	horizont_cross(t_all *all, double angle)
{
	t_search_cross	cross;

	cross.new_x = 0;
	cross.new_y = 0;
	all->params->dir_h = 0;
	all->params->dir_v = 0;
	if (sin(angle) < 0)
	{
		all->params->dir_h = 0;
		cross.delta_y = -1;
		cross.new_y = (int)all->plr->y;
	}
	else if (sin(angle) >= 0)
	{
		all->params->dir_h = 1;
		cross.delta_y = 1;
		cross.new_y = (int)all->plr->y + 1;
	}
	cross.delta_x = 1 / tan(angle);
	cross.new_x = all->plr->x + (cross.new_y - all->plr->y) \
				/ sin(angle) * cos(angle);
	return (fabs(count_ray_h(all, &cross, angle)));
}

double	count_ray_v(t_all *all, t_search_cross	*cross, double angle)
{
	double	ray_len;

	ray_len = INFINITY;
	while (cross->new_x >= 0 && cross->new_x < all->params->map_width)
	{
		if (cross->new_y < 0 || cross->new_y >= all->params->map_height)
			break ;
		if (all->params->map[(int)cross->new_y][(int)cross->new_x - \
							(cross->delta_x == -1 ? 1 : 0)] == '1')
		{
			ray_len = (cross->new_x - all->plr->x) / cos(angle);
			break ;
		}
		cross->new_y += (cross->delta_x / cos(angle)) * sin(angle);
		cross->new_x += cross->delta_x;
	}
	if (cos(angle) < 0)
		all->params->hit_y = 1 - (cross->new_y - (int)cross->new_y);
	else
		all->params->hit_y = cross->new_y - (int)cross->new_y;
	return (ray_len);
}

double	vertical_cross(t_all *all, double angle)
{
	t_search_cross	cross;

	cross.new_x = 0;
	cross.new_y = 0;
	if (cos(angle) >= 0)
	{
		all->params->dir_v = 2;
		cross.delta_x = 1;
		cross.new_x = (int)all->plr->x + 1;
	}
	else if (cos(angle) < 0)
	{
		all->params->dir_v = 3;
		cross.delta_x = -1;
		cross.new_x = (int)all->plr->x;
	}
	cross.delta_y = tan(angle);
	cross.new_y = all->plr->y + (cross.new_x - all->plr->x) \
					/ cos(angle) * sin(angle);
	return (fabs(count_ray_v(all, &cross, angle)));
}

void	cast_rays(t_all *all, int i)
{
	double	start;
	double	dist_h;
	double	dist_v;

	while (i < all->params->width)
	{
		start = all->plr->direction - M_PI / 6 + i \
				* M_PI / 3 / (double)all->params->width;
		dist_h = horizont_cross(all, start) * cos(start - all->plr->direction);
		dist_v = vertical_cross(all, start) * cos(start - all->plr->direction);
		if (dist_h < dist_v)
		{
			all->params->wall_height = (all->params->height / dist_h);
			all->params->dist_to_wall[i] = dist_h;
			draw(all, i, all->params->dir_h);
		}
		else
		{
			all->params->wall_height = (all->params->height / dist_v);
			all->params->dist_to_wall[i] = dist_v;
			draw(all, i, all->params->dir_v);
		}
		i++;
	}
}
