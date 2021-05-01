#include "cub3d.h"

static void	parse_args(char *line, t_all *all, void func(char *l, t_all *all))
{
	all->params->settings += 1;
	func(line, all);
}

static int	check_params(char *line, t_all *all)
{
	int	len;

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
	else
		return (0);
	return (1);
}

void	parser(char *line, t_all *all)
{
	int	i;

	i = 0;
	if (check_params(line, all))
		return ;
	else if (*line == '\0')
	{
		if (all->params->map_start == 1)
			error_close(all, 4);
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
	else if (*line != '\0' && (all->params->settings == 8))
		error_close(all, 2);
	else
		return ;
}
