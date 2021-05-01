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
		check_screen_size(all);
	}
	else
		error_close(all, 5);
	free_array(resolution);
}

static void	is_num(char *array, t_all *all)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!ft_isdigit(array[i]))
			error_close(all, 6);
		i++;
	}
}

static void	get_colors_int(char **str_color, t_all *all, int i)
{
	char	**rgb;
	int		j;

	rgb = NULL;
	j = 0;
	if (i == 2)
	{
		rgb = ft_split(str_color[1], ',');
		while (rgb[j])
		{
			is_num(rgb[j], all);
			j++;
		}
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
