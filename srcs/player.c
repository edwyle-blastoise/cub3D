#include "cub3d.h"

void	ft_cast_rays(t_all *all, int x)
{
	t_player	ray;
	double		start;
	double		end;

	ray = *all->plr;
	start = ray.direction - M_PI / 6;
	end = ray.direction + M_PI / 6;
	if (all->params->width > 200 || all->params->height > 100)
	{
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
}

void	search_plr(t_all *all, int x, int y)
{
	if (ft_strchr("NEWS", all->params->map[y][x]))
	{
		all->plr->x = (double)x + 0.5;
		all->plr->y = (double)y + 0.5;
		if (all->params->map[y][x] == 'N')
			all->plr->direction = 3 * M_PI_2;
		else if (all->params->map[y][x] == 'E')
			all->plr->direction = 2 * M_PI;
		else if (all->params->map[y][x] == 'W')
			all->plr->direction = M_PI;
		else if (all->params->map[y][x] == 'S')
			all->plr->direction = M_PI_2;
	}
}

void	init_player(t_all *all)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (all->params->map[y])
	{
		x = 0;
		while (all->params->map[y][x])
		{
			search_plr(all, x, y);
			x++;
		}
		y++;
	}
}

void	draw_player(t_all *all)
{
	double	x;
	double	y;
	double	x_end;
	double	y_end;

	x = all->plr->x * SCALE;
	y = all->plr->y * SCALE;
	x_end = (all->plr->x + 1) * SCALE;
	y_end = (all->plr->y + 1) * SCALE;
	while (y < y_end && all->params->map[(int)y / SCALE][(int)x / SCALE] != '1')
	{
		while (x < x_end \
			&& all->params->map[(int)y / SCALE][(int)x / SCALE] != '1')
			my_mlx_pixel_put(all->data, x++, y, 0x00FF00);
		x -= SCALE;
		y++;
	}
}
