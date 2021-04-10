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

void    params_init(t_params *params)
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
    params->plr_found = 0;
    params->error = 0;
}

char    **create_map(t_list **head, int size)
{
    int     i;
    t_list  *tmp;
    char    **map;
    
    i = 0;
    tmp = *head;
    if (!(map = ft_calloc(sizeof(char*), size + 1)))
        return (NULL);
    while (tmp)
    {
        map[i] = ft_strdup(tmp->content);
        i++;
        tmp = tmp->next;
    }
    i = 0;
    ft_lstclear(head, &free);
    while (map[i])
    {
        ft_putendl_fd(map[i], 1);
        i++;
    }
    return (map);
}

void    read_map(char *argv1, t_all *all)
{
    char        *line;
    t_list      *head;
    
    line = NULL;
    head = NULL;
    all->params->fd = open(argv1, O_RDONLY);
    params_init(all->params);
    while (get_next_line(all->params->fd, &line) > 0)
    {
        if (all->params->settings == 8)
            ft_lstadd_back(&head, ft_lstnew(line));
        parser(line, all);
    }
    ft_lstadd_back(&head, ft_lstnew(line));
    all->params->map = create_map(&head, ft_lstsize(head));
    check_map(all);
}

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    scale_map(t_data  *data, int x, int y, int color)
{
    int x_end;
    int y_end;

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

void    draw_map(t_all *all)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (all->params->map[y])
    {
        x = 0;
         while (all->params->map[y][x])
        {
            if (all->params->map[y][x] == '1')
                scale_map(all->data, x, y, 0xFFFFFF);
            else
                scale_map(all->data, x, y, all->params->ceilling_color);
            x++;
        }
        y++;
    }
}