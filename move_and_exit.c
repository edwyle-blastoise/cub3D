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

int	check_wall(t_all *all)
{
	double	new_x;
	double	new_y;

	new_y = all->plr->y;
	new_x = all->plr->x;
	if (all->params->key_w || all->params->key_up)
	{
		new_y += 0.2 * sin(all->plr->direction);
		new_x += 0.2 * cos(all->plr->direction);
	}
	if (all->params->key_s || all->params->key_down)
	{
		new_y -= 0.2 * sin(all->plr->direction);
		new_x -= 0.2 * cos(all->plr->direction);
	}
	if (all->params->key_l)
		all->plr->direction -= 0.05;
	if (all->params->key_r)
		all->plr->direction += 0.05;
	if (all->params->key_a)
	{
		new_x += 0.2 * sin(all->plr->direction + 2 * M_PI);
		new_y -= 0.2 * cos(all->plr->direction + 2 * M_PI);
	}
	if (all->params->key_d)
	{
		new_x += 0.2 * sin(all->plr->direction + M_PI);
		new_y -= 0.2 * cos(all->plr->direction + M_PI);
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
	else if (key == W)
		all->params->key_w = 1;
	else if (key == UP)
		all->params->key_up = 1;
	else if (key == S)
		all->params->key_s = 1;
	else if (key == DOWN)
		all->params->key_down = 1;
	else if (key == L)
		all->params->key_l = 1;
	else if (key == R)
		all->params->key_r = 1;
	else if (key == A)
		all->params->key_a = 1;
	else if (key == D)
		all->params->key_d = 1;
		return (0);
}

int	key_release(int key, t_all *all)
{
	if (key == W)
		all->params->key_w = 0;
	else if (key == UP)
		all->params->key_up = 0;
	else if (key == S)
		all->params->key_s = 0;
	else if (key == DOWN)
		all->params->key_down = 0;
	else if (key == L)
		all->params->key_l = 0;
	else if (key == R)
		all->params->key_r = 0;
	else if (key == A)
		all->params->key_a = 0;
	else if (key == D)
		all->params->key_d = 0;
		return (0);
}

void	key_events(t_all *all)
{
	if ((check_wall(all)) == 0)
	{
		cast_rays(all);
		draw_map(all);
		ft_cast_rays(all);
		draw_sprites(all);
		mlx_put_image_to_window(all->data->mlx, all->data->win, all->data->img, 0, 0);
	}
}

int	exit_cub(t_all *all)
{
	close (all->params->fd);
	if (all->params->map)
		free_array(all->params->map);
	exit(0);
}

void	error_close(t_all *all, int i)
{
	(void)all;
	if (i == 1)
		printf("Error\nInvalid file name\n");
	else if (i == 2)
		printf("Error\nIncorrect parameters\n");
	else if (i == 3)
		printf("Error\nThere must be one player on the map\n");
	else if (i == 4)
		printf("Error\nNot valid map\n");
	else if (i == 5)
		printf("Error\nResolution must have two positive int value\n");
	else if (i == 6)
		printf("Error\nColors must have three int value\n");
	else if (i == 7)
		printf("Error\nColors must be in range [0-255]\n");
	else if (i == 8)
		printf("Error\nMemory error\n");
	else if (i == 9)
		printf("Error\nTexture path error\n");
	else if (i == 10)
		printf("Bmp file creation error\n");
	else if (i == 11)
		printf("Incorrect arg name\n");
	if (all->params->map)
		free_array(all->params->map);
	exit (1);
}