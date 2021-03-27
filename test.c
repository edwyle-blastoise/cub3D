#include <stdio.h>
#include "mlx.h"
// #include <math.h>
//-lmlx -framework OpenGL -framework AppKit


typedef struct  s_data {
    void        *img;
    char        *addr;
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
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int         key_hook(int keycode, t_data *data)
{
    printf("Key %d\n", keycode);
    return (0);
}

// int             main(void)
// {
//     t_data  data;
//     void    *mlx;
//     void    *mlx_win;
//     t_data  img;
//     int     x;
//     int     y;

//     x = 5;
//     y = 5;

//     mlx = mlx_init();
//     mlx_win = mlx_new_window(mlx, 640, 480, "Hello world!");
//     img.img = mlx_new_image(mlx, 640, 480);
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

//     while (y++ < 100)
//     {
//         x = 5;
//         while (x++ < 100)
//              my_mlx_pixel_put(&img, x, y, 0xFFFFFF);
//             // mlx_pixel_put(mlx, mlx_win, x, y, 0xFFFFFF);
//     }
//     mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
//     mlx_key_hook(mlx_win, key_hook, &data);
//     mlx_loop(mlx);
// }
