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

int	exit_cub(t_all *all)
{
	close (all->params->fd);
	if (all->params->map)
		free_array(all->params->map);
	exit(0);
}

void	error_close(t_all *all, int i)
{
	if (i == 1)
		printf("Error\nInvalid file name\n");
	else if (i == 2)
		printf("Error\nIncorrect parameters");
	else if (i == 3)
		printf("Error\nThere must be one player on the map");
	else if (i == 4)
		printf("Error\nNot valid map\n");
	else if (i == 5)
		printf("Error\nResolution must have two positive int value");
	else if (i == 6)
		printf("Error\nColors must have three int value");
	else if (i == 7)
		printf("Error\nColors must be in range [0-255]");
	else if (i == 8)
		printf("Error\nMemory error");
	else if (i == 9)
		printf("Error\nTexture path error");
	else if (i == 10)
		printf("Bmp file creation error\n");
	else if (i == 11)
		printf("Incorrect arg name\n");
	if (all->params->map)
		free_array(all->params->map);
	exit (1);
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
}
