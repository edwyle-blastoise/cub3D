#include <stdio.h>
#include "/Users/eblastoi/cub3d/minilibx_mms/mlx.h"
//-lmlx -framework OpenGL -framework AppKit
//gcc -g -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit gnl/*c libmlx.a libft.a cub3d.c parser.c player.c create_map.c raycasting.c check_map.c textures.c draw.c sprites.c


typedef struct  s_data {
    void        *img;
    int         *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct  s_point
{
    int         x;
    int         y;
}               t_point;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    int    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int         key_hook(int keycode, t_data *data)
{
    printf("Key %d\n", keycode);
    return (0);
}

int             main(void)
{
    // t_data  data;
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    int     x;
    int     y;
    char    *relative_path = "/Users/eblastoi/cub3d/textures/barrel.xpm";
    int     img_width;
    int     img_height;
    int     addr;

    img_width = 0;
    img_height = 0;
    x = 0;
    y = 0;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 640, 480, "Hello world!");
    img.img = mlx_new_image(mlx, 640, 480);
    // img.addr = (int*)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    img.img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    img.addr = (int*)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    while (y < img_height)
    {
        x = 0;
        while (x < img_width)
        {
             addr = img_width * y + x * (img.bits_per_pixel / 8);
             my_mlx_pixel_put(&img, x, y, *((unsigned int*)(img.addr + addr)));
            // mlx_pixel_put(mlx, mlx_win, x, y, 0xFFFFFF);
            x++;
        }
        y++;
    }
    mlx_destroy_image(mlx, img.img);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    // mlx_key_hook(mlx_win, key_hook, &data);
    mlx_loop(mlx);
}