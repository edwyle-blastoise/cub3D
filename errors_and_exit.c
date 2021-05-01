#include "cub3d.h"

int	exit_cub(t_all *all)
{
	close (all->params->fd);
	if (all->params->map)
		free_array(all->params->map);
	exit(0);
}

void	error_close(t_all *all, int i)
{
	if (i == 1)
		printf("Error\nInvalid file name\n");
	else if (i == 2)
		printf("Error\nIncorrect parameters\n");
	else if (i == 3)
		printf("Error\nThere must be one player on the map\n");
	else if (i == 4)
		printf("Error\nNot valid map\n");
	else if (i == 5)
		printf("Error\nResolution must have two positive int value\n");
	else if (i == 6)
		printf("Error\nColors must have three int value\n");
	else if (i == 7)
		printf("Error\nColors must be in range [0-255]\n");
	else if (i == 8)
		printf("Error\nMemory error\n");
	else if (i == 9)
		printf("Error\nTexture error\n");
	else if (i == 10)
		printf("Bmp file creation error\n");
	else if (i == 11)
		printf("Incorrect arg name\n");
	if (all->params->map)
		free_array(all->params->map);
	exit (1);
}
