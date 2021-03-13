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

#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "gnl/get_next_line.h"

typedef struct  s_params
{
    int         width;
    int         height;
    int         t;
    int         r;
    int         g;
    int         b;
    int         floor_color;
    int         ceilling_color;
}               t_params;

void            params_init(t_params *params)
{
    params->width = 0;
    params->height = 0;
    params->t = 0;
    params->r = 0;
    params->g = 0;
    params->b = 0;
    params->floor_color = 0;
    params->ceilling_color = 0;
}

void    define_resolution(char *line, t_params *params)
{
    char    **resolution;

    resolution = NULL;
    resolution = ft_split(line, ' ');
    params->width = ft_atoi(resolution[1]);
    params->height = ft_atoi(resolution[2]);
    printf("%d %d\n", params->width, params->height);
}

int    create_trgb(int r, int g, int b)
{
    int t;

    t = 0;
    return (t << 24 | r << 16 | g << 8 | b);
}

int    define_color(char *line, t_params *params)
{
    char        **floor_color;
    char        **rgb;
    int         color;

    floor_color = NULL;
    rgb = NULL;
    color = 0;
    floor_color = ft_split(line, ' ');
    rgb = ft_split(floor_color[1], ',');
    params->r = ft_atoi(rgb[0]);
    params->g = ft_atoi(rgb[1]);
    params->b = ft_atoi(rgb[2]);
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

void    parser(char *line, t_params *params)
{
    int i;
    
    i = 0;
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
        // else if (line[i] == '\0')
        else
            return ;
    }
}

int         main(int argc, char **argv)
{
    int         fd;
    char        *line;
    t_params    params;
    
    line = NULL;
    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        params_init(&params);
        while (get_next_line(fd, &line) > 0)
        {
            parser(line, &params);
        }
    }
    // else if (argc == 3)
    // {
        
    // }
    return (0);
}
