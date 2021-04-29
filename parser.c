/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:18:33 by eblastoi          #+#    #+#             */
/*   Updated: 2021/03/11 15:18:36 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	define_resolution(char *line, t_all *all)
{
	char	**resolution;
	int		i;

	resolution = NULL;
	i = 0;
	resolution = ft_split(line, ' ');
	while (resolution[i])
		i++;
	if (i == 3)
	{
		if ((ft_strcmp(resolution[0], "R") != 0))
			error_close(all, 2);
		all->params->width = ft_atoi(resolution[1]);
		all->params->height = ft_atoi(resolution[2]);
		if (all->params->width <= 0 || all->params->height <= 0)
			error_close(all, 5);
	}
	else
		error_close(all, 5);
	free_array(resolution);
}

char	**get_colors_int(char **str_color, t_all *all, int i)
{
	char	**rgb;
	int		j;

	rgb = NULL;
	j = 0;
	if (i == 2)
	{
		rgb = ft_split(str_color[1], ',');
		while (rgb[j])
			j++;
		if (j == 3)
		{
			all->params->r = ft_atoi(rgb[0]);
			all->params->g = ft_atoi(rgb[1]);
			all->params->b = ft_atoi(rgb[2]);
		}
		else
			error_close(all, 6);
	}
	else
		error_close(all, 2);
	free_array(rgb);
	return (rgb);
}

void	define_color(char *line, t_all *all)
{
	char	**str_color;
	int		color;
	int		i;

	str_color = NULL;
	color = 0;
	i = 0;
	str_color = ft_split(line, ' ');
	while (str_color[i])
		i++;
	get_colors_int(str_color, all, i);
	if ((all->params->r >= 0 && all->params->r <= 255) && (all->params->g >= 0 && all->params->g <= 255) \
		&& (all->params->b >= 0 && all->params->b <= 255))
	{
		color = create_trgb(all->params->r, all->params->g, all->params->b);
		if ((ft_strcmp(str_color[0], "F")) == 0)
			all->params->floor_color = color;
		else if ((ft_strcmp(str_color[0], "C")) == 0)
			all->params->ceilling_color = color;
		else
			error_close(all, 2);
	}
	else
		error_close(all, 7);
	free_array(str_color);
}

void	check_text_args(char **textures, t_all *all)
{
	if ((ft_strcmp(textures[0], "NO") == 0))
		all->params->north_texture = ft_strdup(textures[1]);
	else if ((ft_strcmp(textures[0], "SO") == 0))
		all->params->south_texture = ft_strdup(textures[1]);
	else if ((ft_strcmp(textures[0], "WE") == 0))
		all->params->west_texture = ft_strdup(textures[1]);
	else if ((ft_strcmp(textures[0], "EA") == 0))
		all->params->east_texture = ft_strdup(textures[1]);
	else if ((ft_strcmp(textures[0], "S") == 0))
		all->params->sprite_texture = ft_strdup(textures[1]);
	else
		error_close(all, 2);
}

void	define_textures(char *line, t_all *all)
{
	char	**textures;
	int		i;

	textures = NULL;
	i = 0;
	textures = ft_split(line, ' ');
	while (textures[i])
		i++;
	if (i == 2)
		check_text_args(textures, all);
	else
		error_close(all, 2);
	free_array(textures);
}

void	parse_args(char *line, t_all *all, void func(char *l, t_all *all))
{
	all->params->settings += 1;
	func(line, all);
}

void	parser(char *line, t_all *all)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	if (ft_strnstr(line, "R ", len))
		parse_args(line, all, define_resolution);
	else if (ft_strnstr(line, "NO ", len))
		parse_args(line, all, define_textures);
	else if (ft_strnstr(line, "SO ", len))
		parse_args(line, all, define_textures);
	else if (ft_strnstr(line, "WE ", len))
		parse_args(line, all, define_textures);
	else if (ft_strnstr(line, "EA ", len))
		parse_args(line, all, define_textures);
	else if (ft_strnstr(line, "S ", len))
		parse_args(line, all, define_textures);
	else if (ft_strnstr(line, "F ", len))
		parse_args(line, all, define_color);
	else if (ft_strnstr(line, "C ", len))
		parse_args(line, all, define_color);
	else if (*line == '\0')
	{
		if (all->params->map_start == 1)
			error_close(all, 4);
		printf("\n");
	}
	else if ((all->params->settings == 8) && (all->params->map_start == 1))
	{
		while (line[i])
		{
			if (ft_strchr(" 102WNES", line[i]) > 0)
				i++;
			else
				error_close(all, 4);
		}
	}
	else
		return ;
}
