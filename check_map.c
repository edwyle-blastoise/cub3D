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

void     check_map(t_all *all)
{
    int     i;
    int     j;
    int     len;
    int     num_of_strings;
    char    **copy_map;

    i = 0;
    num_of_strings = 0;
    copy_map = all->params->map;
    while (copy_map[i])
         i++;
    num_of_strings = i - 1;
    i = 0;
    while (copy_map[i])
    {
        j = 0;
        len = ft_strlen(copy_map[i]);
        while (j < len)
        {
            if (i == 0 || i == num_of_strings)
            {
                if (copy_map[i][j] != '1' && copy_map[i][j] != ' ')
                {
                    all->params->error = 4;
                    error_close(all->params);
                }
            }
            j++;
        }
        check_player(all, copy_map[i]);
        i++;
    }
    if (all->params->plr_found != 1)
    {
        all->params->error = 5;
        error_close(all->params);
    }
}