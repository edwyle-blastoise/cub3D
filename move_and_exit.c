/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 22:30:05 by eblastoi          #+#    #+#             */
/*   Updated: 2021/04/29 22:30:07 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(int key, t_all *all)
{
	double	new_x;
	double	new_y;

	new_y = all->plr->y;
	new_x = all->plr->x;
	if (key == W || key == UP)
	{
		new_y += 0.3 * sin(all->plr->direction);
		new_x += 0.3 * cos(all->plr->direction);
	}
	if (key == S || key == DOWN)
	{
		new_y -= 0.3 * sin(all->plr->direction);
		new_x -= 0.3 * cos(all->plr->direction);
	}
	if (key == L)
		all->plr->direction -= 0.1;
	if (key == R)
		all->plr->direction += 0.1;
	if (key == A)
	{
		new_x += 0.3 * sin(all->plr->direction + 2 * M_PI);
		new_y -= 0.3 * cos(all->plr->direction + 2 * M_PI);
	}
	if (key == D)
	{
		new_x += 0.3 * sin(all->plr->direction + M_PI);
		new_y -= 0.3 * cos(all->plr->direction + M_PI);
	}
	if ((new_x < all->params->map_width) && (new_y < all->params->map_height))
	{
		if (all->params->map[(int)new_y][(int)new_x] != '1')
		{
			all->plr->x = new_x;
			all->plr->y = new_y;
			return (0);
		}
	}
	return (1);
}


int	key_press(int key, t_all *all)
{
	if (key == ESC)
		exit_cub(all);
	if ((check_wall(key, all)) == 0)
	{
		// draw_player(all);
		// ft_cast_ray(all);
		// draw_floor_and_ceiling(all);
		cast_rays(all);
		draw_map(all);
		ft_cast_rays(all);
		draw_sprites(all);
		mlx_put_image_to_window(all->data->mlx, all->data->win, all->data->img, 0, 0);
	}
	return (0);
}
