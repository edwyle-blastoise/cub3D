#include "cub3d.h"

int    pixel_take(t_all *all, int x, int y, int side)
{
    int *dst;
    int color;
    
    dst = NULL;
    dst = all->text[side].texture_addr + (y * all->text[side].texture_width + x);
    color = *(unsigned int*)dst;
    return (color);
}

void draw_wall(t_all * all, int x, int y, int side)
{
    int dy;
    int dx;
    int offset;
    int color;

    if (side < 2)
        dx = all->params->hit_x * all->text[side].texture_width;
    else
        dx = all->params->hit_y * all->text[side].texture_width;
    offset = all->params->height / 2 - y;
    dy = all->text[side].texture_height * (all->params->wall_height - 2 * offset) / (2 * all->params->wall_height);
    if (dy >= 0 && dy < all->params->height)
    {
        color = pixel_take(all, dx, dy, side);
        my_mlx_pixel_put(all->data, x, y, color);
    }
 }

void    draw(t_all *all, int x, int side)
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

