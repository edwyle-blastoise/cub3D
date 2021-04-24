#include "cub3d.h"

int    pixel_take(t_all *all, int x, int y, int side, double step)
{
    char    *dst;
    double  text_y;
    int     color;
    
    color = 0;
    text_y = (y + all->params->hit_x) * step;
    dst = NULL;
    dst = all->text[side].texture_addr + ((int)text_y * all->text[side].texture_line_length + x * (all->text[side].texture_bpp / 8));
    color = *(unsigned int*)dst;
    return (color);
}

void    draw_wall(t_all *all, int x, int y, int side)
{
    int     dx;
    int     dy;
    double  y_offset;
    double  step;

    dx = 0;
    dy = 0;
    step = (double)all->text[side].texture_height / all->params->wall_height;
    y_offset = 0;

    if (all->params->wall_height > all->params->height)
    {
        y_offset = (all->params->wall_height - all->params->height) / 2;
        all->params->wall_height = all->params->height;
    }
    dx = all->text[side].texture_width * all->params->hit_x;
    if (y_offset > 0)
        dy = step * y_offset;
    my_mlx_pixel_put(all->data, x, y, pixel_take(all, dx, dy, side, step));
}

void    draw_floor_and_ceiling(t_all *all, int x, int side)
{
    int y;

    y = 0;
    while (y < all->params->height)
    {
        if (y < (all->params->height - all->params->wall_height) / 2)
            my_mlx_pixel_put(all->data, x, y, all->params->ceilling_color);
        else if ((y >= (all->params->height - all->params->wall_height) / 2) && (y < (all->params->height + all->params->wall_height) / 2))
        // my_mlx_pixel_put(all->data, x, y, 0xFF5533);
            draw_wall(all, x, y, side);
        else if ((y >= (all->params->height + all->params->wall_height) / 2) && (y < all->params->height - 1))
            my_mlx_pixel_put(all->data, x, y, all->params->floor_color);
        y++;
    }
}