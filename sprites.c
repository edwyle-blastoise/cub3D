/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:38:15 by eblastoi          #+#    #+#             */
/*   Updated: 2021/04/28 16:38:22 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dist_to_sprite(t_all *all, int num)
{
	double dist = hypot(all->spr[num]->x - all->plr->x + 0.5, all->spr[num]->y - all->plr->y + 0.5);
	all->spr[num]->dist = 0;
	//all->spr[num]->dist *= cos(all->spr[num]->dir);
	//if (hypot(all->plr->x - all->spr[num]->x + 0.5, all->plr->y - all->spr[num]->y + 0.5) > all->spr[num]->dist)
	if (dist >= all->spr[num]->dist)
	{
		all->spr[num]->dist = dist;// hypot(all->plr->x - (all->spr[num]->x + 0.5), all->plr->y - (all->spr[num]->y + 0.5));
		//all->spr[num]->dist /= cos(all->spr[num]->dir);
		// printf("Dist = %lf\n", all->spr[num]->dist);
	}
}

void	sprite_dir(t_all *all, int num)
{
	all->spr[num]->dir = 0;
	all->spr[num]->dir = atan2((all->spr[num]->y + 0.5 - all->plr->y), (all->spr[num]->x + 0.5 - all->plr->x));
	while (all->spr[num]->dir - all->plr->direction > M_PI)
		all->spr[num]->dir -= 2 * M_PI;
	while (all->spr[num]->dir - all->plr->direction < - M_PI)
		all->spr[num]->dir += 2 * M_PI;
	all->spr[num]->dir -= all->plr->direction;
	// printf("Dir = %lf\n", all->spr[num]->dir);
}

int	get_sprite_color(t_all *all, int num, int i, int j, int color)
{
	int		tex_w;
	int		tex_h;
	double	x;
	double	y;
	int t = 4;

	x = (double)all->spr[num]->sprite_height / all->text[t].texture_width;
	y = (double)all->spr[num]->sprite_height / all->text[t].texture_height;
	tex_w = (int)(i / x);
	tex_h = (int)(j / y);
	if (tex_h > all->text[t].texture_height)
		tex_h = all->text[t].texture_height;
	if (tex_w > all->text[t].texture_width)
		tex_w = all->text[t].texture_width;
	color = *(unsigned int *)(all->text[t].texture_addr + \
	(tex_h * all->text[t].texture_width + tex_w));// * (all->text[4].texture_bpp / 8)));
	return (color);
}

void	draw_sprite(t_all *all, int num)
{
	int	y;
	int	x;
	int	color;
	int dy = all->spr[num]->sprite_height;
	double asp = all->params->width / all->params->height;
	int dx = (all->spr[num]->sprite_height * asp);

	x = 0;
	while (x < dx)
	{
		if (all->spr[num]->offset_x + x >= 0 && all->spr[num]->offset_x + x < all->params->width &&
			all->params->dist_to_wall[(int)all->spr[num]->offset_x + x] >=
			all->spr[num]->dist)
		{
			if (all->params->dist_to_wall[(int)all->spr[num]->offset_x + x] < all->spr[num]->dist) {
				printf("save dist = %lf, sprite dist = %lf\n", all->params->dist_to_wall[(int)all->spr[num]->offset_x + x], all->spr[num]->dist);
			}
			y = 0;
			while (y < dy)
			{
				color = get_sprite_color(all, num, x, y, 0);

				if ((all->spr[num]->offset_y + y >= 0) && (all->spr[num]->offset_y + y < all->params->height)
					&& color != 0x000000)
					my_mlx_pixel_put(all->data, all->spr[num]->offset_x + x, all->spr[num]->offset_y + y, color);
				y++;
			}
		}
		x++;
	}
}

void	sprites_init(t_all *all)
{
	int num;
	int x;
	int y;

	num = 0;
	if (!(all->spr = (t_sprites**)ft_calloc((all->params->sprites + 1), sizeof(t_sprites*))))
		error_close(all, 8);
	while (num < all->params->sprites)
	{
		if (!(all->spr[num] = (t_sprites*)ft_calloc(1, sizeof(t_sprites))))
			error_close(all, 8);
		num++;
	}
	num = 0;
	y = 0;
	while (y < all->params->map_height)
	{
		x = 0;
		while (x < all->params->map_width)
		{
			if (all->params->map[y][x] == '2')
			{
				all->spr[num]->y = y;
				all->spr[num]->x = x;
				num++;
			}
			x++;
		}
		y++;
	}
}

void	draw_sprites(t_all *all)
{
	int	num;
	double size;
	double asp = all->params->width / ((double)all->params->height);
	printf("asp=%lf\n", asp);
	num = 0;
	while (num < all->params->sprites)
	{
		sprite_dir(all, num);
		dist_to_sprite(all, num);

		//all->spr[num]->sprite_height = (all->params->height / all->spr[num]->dist);
		//all->spr[num]->offset_x = all->params->width / 2 - 1 + tan(all->spr[num]->dir) * all->params->height - all->spr[num]->sprite_height / 2;
		//all->spr[num]->offset_y = all->params->height / 2 - all->spr[num]->sprite_height / 2;
		size = all->params->width / (all->spr[num]->dist);// * asp; //* cos(all->spr[num]->dir
		all->spr[num]->sprite_height = size;
		size /= 2;
		printf("num=%d size = %lf, dir=%lf sin=%lf dist=%lf\n", num, all->spr[num]->sprite_height, all->spr[num]->dir, sin(all->spr[num]->dir), all->spr[num]->dist);
		all->spr[num]->offset_x = all->params->width / 2 + tan(all->spr[num]->dir)  * all->params->width - (size);

		//all->spr[num]->offset_x = all->params->width / 2  - size - all->spr[num]->dir * (all->params->width  / (M_PI / 3));

		//all->spr[num]->offset_x = (all->spr[num]->dir - all->plr->direction) / (M_PI / 3) *(all->params->width / 2) + (all->params->width/2)/2 - size;
		all->spr[num]->offset_y = all->params->height / 2 - size;
		if (fabs(all->spr[num]->dir) < M_PI_2 &&
		//if ((all->spr[num]->dir) < M_PI_2 &&
			all->spr[num]->sprite_height < 2000)// all->params->height * 7 / 9 )
		{
			draw_sprite(all, num);
			//printf("num= %d [%lf:%lf]\n", num, all->spr[num]->x, all->spr[num]->y );
		}
		num++;
	}
}


