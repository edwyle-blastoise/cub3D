#include "cub3d.h"

void error_close(t_all *all)
{
    if (all->params->error == 1)
        printf("Error\nInvalid file name\n");
    else if (all->params->error == 2)
         printf("Error\nInvalid parameter");
    else if (all->params->error == 3)
        printf("Error\nIncorrect number of parameters");
    else if (all->params->error == 4)
        printf("Error\nThere must be one player on the map");
    else if (all->params->error == 5)
       printf("Error\nNot valid map\n");
    else if (all->params->error == 6)
        printf("Error\nResolution must have two positive int value");
    else if (all->params->error == 7)
        printf("Error\nColors must have three int value");
    else if (all->params->error == 8)
        printf("Error\nColors must be in range [0,255]");
    else if (all->params->error == 9)
        printf("Error\nMemory error");
    else if (all->params->error == 10)
        printf("Error\nTexture path error");
    else
        printf("Error\n");
    // free all malloc
    close (all->params->fd);
    free (all->params->map);
    exit (1);
}

int    check_wall(int key, t_all *all)
{
    double  new_x;
    double  new_y;

    new_y = all->plr->y;
    new_x = all->plr->x;
    if (key == W || key == UP)
    {
        new_y += 0.3 * sin(all->plr->direction);
        new_x += 0.3 * cos(all->plr->direction);
    }
    if (key == S || key == DOWN)
    {
        new_y -= 0.3 * sin(all->plr->direction);
        new_x -= 0.3 * cos(all->plr->direction);
    }
    if (key == L)
        all->plr->direction -= 0.1;
    if (key == R)
        all->plr->direction += 0.1;
    if (key == A)
    {
        new_x += 0.3 * sin(all->plr->direction + 2 * M_PI);
        new_y -= 0.3 * cos(all->plr->direction + 2 * M_PI);
    }
    if (key == D)
    {
        new_x += 0.3 * sin(all->plr->direction + M_PI);
        new_y -= 0.3 * cos(all->plr->direction + M_PI);
    }
    if ((new_x < all->params->map_width) && (new_y < all->params->map_height))
    {
        if (all->params->map[(int)new_y][(int)new_x] != '1')
        {
            all->plr->x = new_x;
            all->plr->y = new_y;
            return (0);
        }
    }
    return (1);
}
