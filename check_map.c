/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:46:25 by eblastoi          #+#    #+#             */
/*   Updated: 2021/04/10 16:46:40 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    make_rectangle_map(t_all *all)
{
    int     i;
    int     j;
    int     len;
    char*   remainder;
    
    i = 0;
    remainder = NULL;
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
        if (len < all->params->map_width)
        {
            j = 0;
            if (!(remainder = ft_calloc(sizeof(char*), (all->params->map_width - len) + 1)))
            {
                all->params->error = 11;
                error_close(all->params);
            }
            while (j < (all->params->map_width - len))
            {
                remainder[j] = ' ';
                j++;
            }
            all->params->map[i] = ft_strjoin(all->params->map[i], remainder);
        }
        i++;
    }
}

void    check_player(t_all *all, char *line)
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

void    check_close_map(t_all *all, int len, int i)
{
    int     j;

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
            {
                all->params->error = 9;
                error_close(all->params);
            }
        }
        j++;
    }
}

void     check_map(t_all *all)
{
    int     i;
    int     j;
    int     len;

    i = 0;
    while (all->params->map[i])
    {
        if (ft_strchr(all->params->map[i], '1'))
            all->params->map_height++;
        else
        {
            all->params->error = 5;
            error_close(all->params);
        }
        i++;
    }
    i = 0;
    while (all->params->map[i])
    {
        j = 0;
        len = ft_strlen(all->params->map[i]);
        if (i == 0 || i == all->params->map_height)
        {
            while (j < len)
            {
                if (all->params->map[i][j] == '1' && (all->params->map[i][j + 1] != ' '))
                if (all->params->map[i][j] != '1' && all->params->map[i][j] != ' ')
                {
                    all->params->error = 5;
                    error_close(all->params);
                }
                j++;
            }
        }
        else
            check_close_map(all, len, i);
        check_player(all, all->params->map[i]);
        i++;
    }
    if (all->params->plr_found != 1)
    {
        all->params->error = 4;
        error_close(all->params);
    }
}