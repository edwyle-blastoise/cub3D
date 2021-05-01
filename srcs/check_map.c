#include "cub3d.h"

static void	filling_lines_with_spaces(t_all *all, int len, int i)
{
	int			j;
	static char	*tmp;
	static char	*remainder;

	remainder = NULL;
	tmp = NULL;
	if (len < all->params->map_width)
	{
		j = 0;
		remainder = ft_calloc(sizeof(char *), (all->params->map_width - len));
		if (!remainder)
			error_close(all, 8);
		while (j < (all->params->map_width - len))
		{
			remainder[j] = ' ';
			j++;
		}
		remainder[j] = '\0';
		tmp = all->params->map[i];
		all->params->map[i] = ft_strjoin(all->params->map[i], remainder);
		free(tmp);
		free(remainder);
	}
}

static void	make_rectangle_map(t_all *all)
{
	int		i;
	int		len;

	i = 0;
	while (all->params->map[i])
	{
		len = ft_strlen(all->params->map[i]);
		if (len > all->params->map_width)
			all->params->map_width = len;
		i++;
	}
	i = 0;
	while (all->params->map[i])
	{
		len = ft_strlen(all->params->map[i]);
		filling_lines_with_spaces(all, len, i);
		i++;
	}
}

void	check_player(t_all *all, char *line)
{
	while (*line)
	{
		if (*line == 'N' || *line == 'E' || *line == 'W' || *line == 'S')
			all->params->plr_found += 1;
		else if (*line == '2')
			all->params->sprites++;
		line++;
	}
}

static void	check_close_map(t_all *all, int len, int i)
{
	int	j;

	j = 0;
	while (j < len)
	{
		if ((all->params->map[i][j] != '1') && (all->params->map[i][j] != ' '))
		{
			if ((all->params->map[i][j - 1] == ' ') \
			|| (all->params->map[i][j + 1] == ' ') \
			|| (all->params->map[i + 1][j] == ' ') \
			|| (all->params->map[i + 1][j + 1] == ' ') \
			|| (all->params->map[i + 1][j - 1] == ' ') \
			|| (all->params->map[i - 1][j] == ' ') \
			|| (all->params->map[i - 1][j + 1] == ' ') \
			|| (all->params->map[i - 1][j - 1] == ' '))
				error_close(all, 4);
		}
		j++;
	}
}

void	check_first_last_lines(t_all *all, int i)
{
	int	j;
	int	len;

	while (all->params->map[i])
	{
		j = 0;
		len = ft_strlen(all->params->map[i]);
		if (i == 0 || i == (all->params->map_height - 1))
		{
			while (j < len)
			{
				if ((all->params->map[i][j] != '1') \
					&& (all->params->map[i][j] != ' '))
					error_close(all, 4);
				j++;
			}
		}
		else
		{
			make_rectangle_map(all);
			check_close_map(all, len, i);
		}
		i++;
	}
}
