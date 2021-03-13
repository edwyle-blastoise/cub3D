#include <fcntl.h>
#include "minilibx_opengl/mlx.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"

typedef struct  s_data
{
    void        *mlx;
    void        *win;
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

typedef struct s_all
{
    t_data      *data;
    char        **map;
}               t_all;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

char            **create_map(t_list **head, int size)
{
    // t_data data;
    t_list *tmp = *head;

    char    **map;
    int     i;
    
    map = ft_calloc(sizeof(char*), size + 1);
    i = 0;
    while (tmp)
    {
        map[i] = ft_strdup(tmp->content);
        i++;
        tmp = tmp->next;
    }
    // i = 0;
    // ft_lstclear(head, &free);
    // while (map[i])
    //     ft_putendl_fd(map[i], 1);
    return (map);
}

char         **read_map(char *argv1)
{
    int fd;
    int size;
    char *line;
    t_list *head = NULL;

    size = 0;
    line = NULL;
    fd = open(argv1, O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        ft_lstadd_back(&head, ft_lstnew(line));
        size++;
        line = NULL;
    }
    close(fd);
    ft_lstadd_back(&head, ft_lstnew(line));
    size++;
    return (create_map(&head, size));
}

void      draw_map(t_all *all)
{
    t_point point;

    ft_bzero(&point, sizeof(t_point));
    while (all->map[point.y])
    {
        point.x = 0;
         while (all->map[point.y][point.x])
        {
            if (all->map[point.y][point.x] == '1')
                my_mlx_pixel_put(all->data->img, point.x, point.y, 0xFFFFFF);
            point.x++;
        }
        point.y++;
    }
}

int             main(int argc, char **argv)
{
    (void)argc;
    t_data  data;
    t_all   all;
    // void    *mlx;
    // void    *mlx_win;

    if (argc == 2)
        all.map = read_map(argv[1]);
    else
        ft_putendl_fd("need a map", 2);
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
    data.img = mlx_new_image(data.mlx, 1920, 1080);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    all.data = &data;
    // while (img.map[point.y])
    // {
    //     point.x = 0;
    //     while (img.map[point.y][point.x])
    //     {
    //         if (img.map[point.y][point.x] == '1')
    //         my_mlx_pixel_put(&img, point.x, point.y, 0xFFFFFF);
    //         point.x++;
    //     }
    //     point.y++;
    // }

    draw_map(&all);

    // while (y++ < 100)
    // {
    //     x = 5;
    //     while (x++ < 100)
    //          my_mlx_pixel_put(&img, x, y, 0x00FF0000);
    // }
    // mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(data.mlx);
}
