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

void    define_resolution(char *line, t_params *params)
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
        params->width = ft_atoi(resolution[1]);
        params->height = ft_atoi(resolution[2]);
    }
    else
    {
        printf("Error\nResolution must have two int value");
        error_close(params->fd);
    }
    printf("%d %d\n", params->width, params->height);
}

int     create_trgb(int r, int g, int b)
{
    int t;

    t = 0;
    return (t << 24 | r << 16 | g << 8 | b);
}

int     define_color(char *line, t_params *params)
{
    char        **str_color;
    char        **rgb;
    int         color;
    int         i;

    str_color = NULL;
    rgb = NULL;
    color = 0;
    i = 0;
    str_color = ft_split(line, ' ');
    while (str_color[i])
        i++;
    if (i == 2)
    {
        rgb = ft_split(str_color[1], ',');
        params->r = ft_atoi(rgb[0]);
        params->g = ft_atoi(rgb[1]);
        params->b = ft_atoi(rgb[2]);
    }
    else if (i == 4)
    {
        params->r = ft_atoi(str_color[1]);
        params->g = ft_atoi(str_color[2]);
        params->b = ft_atoi(str_color[3]);
    }
    else
        printf("Error\nColors must have three int value");
    if ((params->r >= 0 && params->r <= 255) && (params->g >= 0 && params->g <= 255) \
        && (params->b >= 0 && params->b <= 255))
        {
            color = create_trgb(params->r, params->g, params->b);
            return (color);
        }
    else
        printf("Error\nColors must be in range [0,255]");
    return (0);
}

int    check_map(const char *line)
{
    int i;
    int len;

    i = 1;
    len = ft_strlen(line);
    while (i < len)
    {
        if (line[i] == '1' || line[i] == '0' || line[i] == '2' || line[i] == ' ')
        i++;
    }
    if (line[i] == '1')
        return (0);
    else
        return (1);
}

void    parser(char *line, t_params *params)
{
    int i;
    // t_list      *head;
    
    i = 0;
    // head = NULL;
    while (line[i])
    {
        if (line[i] == 'R' && line[++i] == ' ') //resolution;
        {
            printf("R ");
            define_resolution(line, params);
        }
        else if (line[i] == 'N' && line[++i] == 'O' && line[++i] == ' ')  //north_texture;
        {
            printf("NO\n");
        }
        else if (line[i] == 'S' && line[++i] == 'O' && line[++i] == ' ') //south_texture;
        {
            printf("SO\n");
        }
        else if (line[i] == 'W' && line[++i] == 'E' && line[++i] == ' ') //west_texture;
        {
            printf("WE\n");
        }
        else if (line[i] == 'E' && line[++i] == 'A' && line[++i] == ' ') //east_texture;
        {
            printf("EA\n");
        }
        else if (line[i] == 'S' && line[++i] == ' ') //sprite_texture;
        {
            printf("S\n");
        }
        else if (line[i] == 'F' && line[++i] == ' ') //floor_color;
        {
            params->floor_color = define_color(line, params);
            printf("F_color: %d\n", params->floor_color);
        }
        else if (line[i] == 'C' && line[++i] == ' ') //ceilling_color;
        {
            params->ceilling_color = define_color(line, params);
            printf("C_color: %d\n", params->ceilling_color);
        }
        // else if (line[i] == ' ' || line[i] == '1')
        // {
        //     if ((check_map(line) == 0))

        // }
        else
            return ;
    }
}

//проверить символы карты
//посчитать количество строк
//сделать флаг наличия ирока
//проверить, что в карте нет пустых строк
//проверить, что после карты в файле ничего больше нет