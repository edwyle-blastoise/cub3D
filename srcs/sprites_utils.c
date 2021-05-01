#include "cub3d.h"

void	define_spr_coor(t_all *all)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (y < all->params->map_height)
	{
		x = 0;
		while (x < all->params->map_width)
		{
			if (all->params->map[y][x] == '2')
			{
				all->spr[i]->y = y;
				all->spr[i]->x = x;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	sprites_init(t_all *all)
{
	int	i;

	i = 0;
	all->spr = (t_sprites **)ft_calloc((all->params->sprites + 1), \
				sizeof(t_sprites *));
	if (!all->spr)
		error_close(all, 8);
	while (i < all->params->sprites)
	{
		all->spr[i] = (t_sprites *)ft_calloc(1, sizeof(t_sprites));
		if (!all->spr[i])
			error_close(all, 8);
		i++;
	}
	define_spr_coor(all);
}
