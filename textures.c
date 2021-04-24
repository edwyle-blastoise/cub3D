#include "cub3d.h"

void	buff_textures(t_all *all)
{
    int     i;

    i = 0;
    all->text[0].texture_path = all->params->north_texture;
	all->text[1].texture_path = all->params->south_texture;
	all->text[2].texture_path = all->params->west_texture;
	all->text[3].texture_path = all->params->east_texture;
	all->text[4].texture_path = all->params->sprite_texture;
    while (i < 5)
    {
        all->text[i].texture_img = mlx_xpm_file_to_image(all->data->mlx, all->text[i].texture_path, &all->text[i].texture_width, &all->text[i].texture_height);
        all->text[i].texture_addr = mlx_get_data_addr(all->text[i].texture_img, &all->text[i].texture_bpp, &all->text[i].texture_line_length, &all->text[i].texture_endian);
        i++;
    }
}