#include "cub3d.h"

void	dist_to_sprite(t_all *all, int i)
{
	double	dist;

	dist = hypot(all->spr[i]->x - all->plr->x + 0.5, \
		all->spr[i]->y - all->plr->y + 0.5);
	all->spr[i]->dist = 0;
	if (dist >= all->spr[i]->dist)
		all->spr[i]->dist = dist;
}

void	sprite_dir(t_all *all, int i)
{
	all->spr[i]->dir = 0;
	all->spr[i]->dir = atan2((all->spr[i]->y + 0.5 - all->plr->y), \
		(all->spr[i]->x + 0.5 - all->plr->x));
	while (all->spr[i]->dir - all->plr->direction > M_PI)
		all->spr[i]->dir -= 2 * M_PI;
	while (all->spr[i]->dir - all->plr->direction < -M_PI)
		all->spr[i]->dir += 2 * M_PI;
	all->spr[i]->dir -= all->plr->direction;
}

int	get_sprite_color(t_all *all, int i, int x, int y)
{
	int		tex_w;
	int		tex_h;
	double	dx;
	double	dy;
	int		color;

	color = 0;
	dx = (double)all->spr[i]->sprite_size / all->text[4].texture_width;
	dy = (double)all->spr[i]->sprite_size / all->text[4].texture_height;
	tex_w = (int)(x / dx);
	tex_h = (int)(y / dy);
	if (tex_h > all->text[4].texture_height)
		tex_h = all->text[4].texture_height;
	if (tex_w > all->text[4].texture_width)
		tex_w = all->text[4].texture_width;
	color = *(unsigned int *)(all->text[4].texture_addr + \
	(tex_h * all->text[4].texture_width + tex_w));
	return (color);
}

void	draw_sprite(t_all *all, int i)
{
	int		y;
	int		x;

	x = 0;
	while (x < all->spr[i]->sprite_size)
	{
		if (all->spr[i]->offset_x + x >= 0 && all->spr[i]->offset_x + x < all->params->width \
			&& all->params->dist_to_wall[(int)all->spr[i]->offset_x + x] \
			>= all->spr[i]->dist)
		{
			y = 0;
			while (y < all->spr[i]->sprite_size)
			{
				if ((all->spr[i]->offset_y + y >= 0) && (all->spr[i]->offset_y + y < all->params->height) \
					&& (get_sprite_color(all, i, x, y)) != 0x000000)
					my_mlx_pixel_put(all->data, all->spr[i]->offset_x + x, all->spr[i]->offset_y + y, \
									get_sprite_color(all, i, x, y));
				y++;
			}
		}
		x++;
	}
}

void	draw_sprites(t_all *all)
{
	int		i;
	double	size;

	i = 0;
	while (i < all->params->sprites)
	{
		sprite_dir(all, i);
		dist_to_sprite(all, i);
		size = all->params->width / (all->spr[i]->dist);
		all->spr[i]->sprite_size = size;
		size /= 2;
		all->spr[i]->offset_x = all->params->width / 2 + \
			tan(all->spr[i]->dir) * all->params->width - (size);
		all->spr[i]->offset_y = all->params->height / 2 - size;
		if (fabs(all->spr[i]->dir) < M_PI_2 \
			&& all->spr[i]->sprite_size < 2000)
			draw_sprite(all, i);
		i++;
	}
}
