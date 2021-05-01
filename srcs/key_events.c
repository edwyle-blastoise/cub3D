#include "cub3d.h"

int	check_wall(t_all *all, double new_x, double new_y)
{
	if ((new_x < all->params->map_width) && (new_y < all->params->map_height))
	{
		if (all->params->map[(int)new_y][(int)new_x] != '1')
		{
			all->plr->x = new_x;
			all->plr->y = new_y;
			return (1);
		}
	}
	return (0);
}

int	check_key(t_all *all, double new_x, double new_y)
{
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
	return (check_wall(all, new_x, new_y));
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
	double	new_x;
	double	new_y;

	new_y = all->plr->y;
	new_x = all->plr->x;
	if (check_key(all, new_x, new_y))
	{
		cast_rays(all, 0);
		draw_sprites(all);
		ft_cast_rays(all, 0);
		draw_map(all);
		mlx_put_image_to_window(all->data->mlx, all->data->win, \
			all->data->img, 0, 0);
	}
}
