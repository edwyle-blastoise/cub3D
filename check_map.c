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
    int     max_len;
    char*   remainder;
    
    i = 0;
    remainder = NULL;
    while (all->params->map[i])
    {
        len = ft_strlen(all->params->map[i]);
        if (len > max_len)
            max_len = len;
        i++;
    }
    i = 0;
    while (all->params->map[i])
    {
        len = ft_strlen(all->params->map[i]);
        if (len < max_len)
        {
            j = 0;
            remainder = ft_calloc(sizeof(char*), (max_len - len) + 1);
            while (j < (max_len - len))
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
        {
            all->params->plr_found += 1;
            all->plr->direction = *line;
        }
        line++;
    }
}

void    check_close_map(t_all *all)
{
    int     i;
    int     j;
    int     length;
    int     strings;

    i = 0;
    strings = 0;
    while (all->params->map[i])
    {
        if (ft_strchr(all->params->map[i], '1'))
            strings++;
        i++;
    }
    i = 0;
    while (++i < strings)
    {
        j = 0;
        length = ft_strlen(all->params->map[i]);
        while (++j < length)
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
        }
    }
}

void     check_map(t_all *all)
{
    int     i;
    int     j;
    int     len;
    int     num_of_strings;

    i = 0;
    num_of_strings = 0;
    while (all->params->map[i])
         i++;
    num_of_strings = i - 1;
    i = 0;
    while (all->params->map[i])
    {
        j = 0;
        len = ft_strlen(all->params->map[i]);
        if (i == 0 || i == num_of_strings)
        {
            while (j < len)
            {
                if (all->params->map[i][j] != '1' && all->params->map[i][j] != ' ')
                {
                    all->params->error = 5;
                    error_close(all->params);
                }
                j++;
            }
        }
        check_player(all, all->params->map[i]);
        i++;
    }
    check_close_map(all);
    if (all->params->plr_found != 1)
    {
        all->params->error = 4;
        error_close(all->params);
    }
}