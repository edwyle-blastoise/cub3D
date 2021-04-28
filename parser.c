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

void    define_resolution(char *line, t_all *all)
{
    char    **resolution;
    int     i;

    resolution = NULL;
    i = 0;
    resolution = ft_split(line, ' ');
    while (resolution[i])
        i++;
    if (i == 3)
    {
        if ((ft_strcmp(resolution[0], "R") != 0))
        {
            all->params->error = 2;
            error_close(all);
        }
        all->params->width = ft_atoi(resolution[1]);
        all->params->height = ft_atoi(resolution[2]);
        if (all->params->width <= 0 || all->params->height <= 0)
        {
            all->params->error = 6;
            error_close(all);
        }
    }
    else
    {
        all->params->error = 6;
        error_close(all);
    }
    printf("%d %d\n", all->params->width, all->params->height);
}

int     create_trgb(int r, int g, int b)
{
    int t;

    t = 0;
    return (t << 24 | r << 16 | g << 8 | b);
}

int     define_color(char *line, t_all *all)
{
    char        **str_color;
    char        **rgb;
    int         color;
    int         i;
    int         j;

    str_color = NULL;
    rgb = NULL;
    color = 0;
    i = 0;
    j = 0;
    str_color = ft_split(line, ' ');
    while (str_color[i])
        i++;
    if (i == 2)
    {
        if ((ft_strcmp(str_color[0], "F") != 0) && (ft_strcmp(str_color[0], "C") != 0))
        {
            all->params->error = 2;
            error_close(all);
        }
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
        {
            all->params->error = 7;
            error_close(all);
        }
    }
    else
    {
        all->params->error = 2;
        error_close(all);
    }
    if ((all->params->r >= 0 && all->params->r <= 255) && (all->params->g >= 0 && all->params->g <= 255) \
        && (all->params->b >= 0 && all->params->b <= 255))
        {
            color = create_trgb(all->params->r, all->params->g, all->params->b);
            return (color);
        }
    else
    {
        all->params->error = 8;
        error_close(all);
    }
    return (0);
}

void    define_textures(char *line, t_all *all)
{
    char    **textures;
    int     i;

    textures = NULL;
    i = 0;
    textures = ft_split(line, ' ');
    while(textures[i])
        i++;
    if (i == 2)
    {
        if ((ft_strcmp(textures[0], "NO") == 0))
            all->params->north_texture = textures[1];
        else if ((ft_strcmp(textures[0], "SO") == 0))
            all->params->south_texture = textures[1];
        else if ((ft_strcmp(textures[0], "WE") == 0))
            all->params->west_texture = textures[1];
        else if ((ft_strcmp(textures[0], "EA") == 0))
            all->params->east_texture = textures[1];
        else if ((ft_strcmp(textures[0], "S") == 0))
            all->params->sprite_texture = textures[1];
        else
        {
            all->params->error = 2;
            error_close(all);
        }
    }
    else
    {
        all->params->error = 2;
        error_close(all);
    }
    printf("%s\n", textures[1]);
}

void    parser(char *line, t_all *all)
{
    int     i;
    int     len;
    
    i = 0;
    len = ft_strlen(line);
    if (ft_strnstr(line, "R ", len))
    {
        printf("R ");
        all->params->settings += 1;
        define_resolution(line, all);
    }
    else if (ft_strnstr(line, "NO ", len))
    {
        all->params->settings += 1;
        printf("NO ");
        define_textures(line, all);
    }
    else if (ft_strnstr(line, "SO ", len))
    {
        all->params->settings += 1;
        printf("SO ");
        define_textures(line, all);
    }
    else if (ft_strnstr(line, "WE ", len))
    {
        all->params->settings += 1;
        printf("WE ");
        define_textures(line, all);
    }
    else if (ft_strnstr(line, "EA ", len))
    {
        all->params->settings += 1;
        printf("EA ");
        define_textures(line, all);
    }
    else if (ft_strnstr(line, "S ", len))
    {
        all->params->settings += 1;
        printf("S ");
        define_textures(line, all);
    }
    else if (ft_strnstr(line, "F ", len))
    {
        all->params->settings += 1;
        all->params->floor_color = define_color(line, all);
        printf("F_color: %d\n", all->params->floor_color);
    }
    else if (ft_strnstr(line, "C ", len))
    {
        all->params->settings += 1;
        all->params->ceilling_color = define_color(line, all);
        printf("C_color: %d\n", all->params->ceilling_color);
    }
    else if (*line == '\0')
    {
        if (all->params->map_start == 1)
        {
            all->params->error = 5;
            error_close(all);
        }
        printf("\n");
    }
    else if ((all->params->settings == 8) && (all->params->map_start == 1))
    {
        while (line[i])
        {
            if (ft_strchr(" 102WNES", line[i]) > 0)
                i++;
            else
            {
                all->params->error = 5;
                error_close(all);
            }
        }
    }
    else
        return ;
}


// проверить параметры цвета на наличие строк