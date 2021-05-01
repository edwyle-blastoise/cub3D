#include "cub3d.h"

static void	check_text_args(char **textures, t_all *all)
{
	if ((ft_strcmp(textures[0], "NO") == 0))
		all->params->north_texture = ft_strdup(textures[1]);
	else if ((ft_strcmp(textures[0], "SO") == 0))
		all->params->south_texture = ft_strdup(textures[1]);
	else if ((ft_strcmp(textures[0], "WE") == 0))
		all->params->west_texture = ft_strdup(textures[1]);
	else if ((ft_strcmp(textures[0], "EA") == 0))
		all->params->east_texture = ft_strdup(textures[1]);
	else if ((ft_strcmp(textures[0], "S") == 0))
		all->params->sprite_texture = ft_strdup(textures[1]);
	else
		error_close(all, 2);
}

void	define_textures(char *line, t_all *all)
{
	char	**textures;
	int		i;

	textures = NULL;
	i = 0;
	textures = ft_split(line, ' ');
	while (textures[i])
		i++;
	if (i == 2)
		check_text_args(textures, all);
	else
		error_close(all, 2);
	free_array(textures);
}

void	buff_textures(t_all *all)
{
	int	i;

	i = 0;
	all->text[0].texture_path = all->params->north_texture;
	all->text[1].texture_path = all->params->south_texture;
	all->text[2].texture_path = all->params->west_texture;
	all->text[3].texture_path = all->params->east_texture;
	all->text[4].texture_path = all->params->sprite_texture;
	while (i < 5)
	{
		all->text[i].texture_img = mlx_xpm_file_to_image(all->data->mlx, all->text[i].texture_path, \
			&all->text[i].texture_width, &all->text[i].texture_height);
		if (!all->text[i].texture_img)
			error_close(all, 9);
		all->text[i].texture_addr = (int *)mlx_get_data_addr(all->text[i].texture_img, &all->text[i].texture_bpp, \
			&all->text[i].texture_line_length, &all->text[i].texture_endian);
		if (!all->text[i].texture_addr)
			error_close(all, 9);
		i++;
	}
}
