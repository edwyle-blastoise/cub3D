/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 17:03:19 by eblastoi          #+#    #+#             */
/*   Updated: 2021/03/27 17:03:22 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map(t_all *all)
{
	int	i;

	i = 0;
	while (all->params->map[i])
	{
		if (ft_strchr(all->params->map[i], '1') \
			|| ft_strchr(all->params->map[i], ' '))
			all->params->map_height++;
		else
			error_close(all, 4);
		check_player(all, all->params->map[i]);
		i++;
	}
	i = 0;
	check_first_last_lines(all, i);
	if (all->params->plr_found != 1)
		error_close(all, 3);
}

void	create_map(t_list **head, int size, t_all *all)
{
	int		i;
	t_list	*tmp;
	char	**map;

	i = 0;
	tmp = *head;
	map = ft_calloc(sizeof(char *), size + 1);
	if (!map)
		return ;
	map[size] = NULL;
	while (tmp)
	{
		map[i] = ft_strdup(tmp->content);
		if (!map[i])
			return ;
		i++;
		tmp = tmp->next;
	}
	i = 0;
	ft_lstclear(head, &free);
	all->params->map = map;
}

void	read_map(char *argv1, t_all *all)
{
	char	*line;
	t_list	*head;

	line = NULL;
	head = NULL;
	all->params->fd = open(argv1, O_RDONLY);
	params_init(all->params);
	while (get_next_line(all->params->fd, &line) > 0)
	{
		if ((all->params->settings == 8) && ((ft_strchr(line, '1')) || \
			(ft_strchr(line, ' '))))
		{
			all->params->map_start = 1;
			ft_lstadd_back(&head, ft_lstnew(ft_strdup(line)));
		}
		parser(line, all);
		free(line);
	}
	ft_lstadd_back(&head, ft_lstnew(ft_strdup(line)));
	free(line);
	if (all->params->settings != 8)
		error_close(all, 2);
	create_map(&head, ft_lstsize(head), all);
	check_map(all);
}

void	scale_map(t_data *data, int x, int y, int color)
{
	int	x_end;
	int	y_end;

	x_end = (x + 1) * SCALE;
	y_end = (y + 1) * SCALE;
	x *= SCALE;
	y *= SCALE;
	while (y < y_end)
	{
		while (x < x_end)
			my_mlx_pixel_put(data, x++, y, color);
		x -= SCALE;
		y++;
	}
}

void	draw_map(t_all *all)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (all->params->map[y])
	{
		x = 0;
		while (all->params->map[y][x])
		{
			if (all->params->map[y][x] == '1')
				scale_map(all->data, x, y, 0xFFFFFF);
			else if (all->params->map[y][x] == '2')
				scale_map(all->data, x, y, 0x334455);
			x++;
		}
		y++;
	}
}
