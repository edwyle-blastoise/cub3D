/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 22:29:42 by eblastoi          #+#    #+#             */
/*   Updated: 2021/04/29 22:29:45 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = NULL;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int r, int g, int b)
{
	int	t;

	t = 0;
	return (t << 24 | r << 16 | g << 8 | b);
}

void	free_array(char **array)
{
	int i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	params_init(t_params *params)
{
	params->settings = 0;
	params->width = 0;
	params->height = 0;
	params->t = 0;
	params->r = 0;
	params->g = 0;
	params->b = 0;
	params->floor_color = 0;
	params->ceilling_color = 0;
	params->floor_color = 0;
	params->map_start = 0;
	params->map_height = 0;
	params->map_width = 0;
	params->plr_found = 0;
	params->error = 0;
	params->sprites = 0;
	params->key_w = 0;
	params->key_up = 0;
	params->key_down = 0;
	params->key_a = 0;
	params->key_s = 0;
	params->key_d = 0;
	params->key_l = 0;
	params->key_r = 0;
	params->dist_to_wall = NULL;
}

void	check_screen_size(t_all *all)
{
	mlx_get_screen_size(all->data->mlx, &all->params->screen_width, &all->params->screen_height);
	if (all->params->width > all->params->screen_width)
		all->params->width = all->params->screen_width;
	if (all->params->height > all->params->screen_height)
		all->params->height = all->params->screen_height;
}