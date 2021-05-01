#include "cub3d.h"

static int	main_loop(t_all *all)
{
	cast_rays(all);
	draw_sprites(all);
	ft_cast_rays(all);
	draw_map(all);
	key_events(all);
	return (0);
}

static void	start_cub(t_all *all)
{
	init_player(all);
	sprites_init(all);
	all->data->mlx = mlx_init();
	all->data->win = mlx_new_window(all->data->mlx, all->params->width, \
		all->params->height, "cub3D");
	all->data->img = mlx_new_image(all->data->mlx, all->params->width, \
		all->params->height);
	all->data->addr = mlx_get_data_addr(all->data->img, &all->data->bits_per_pixel, \
		&all->data->line_length, &all->data->endian);
	all->params->dist_to_wall = (double*)malloc(sizeof(double) * all->params->width + 10);
	if (!all->params->dist_to_wall)
		error_close(all, 8);
	buff_textures(all);
	mlx_put_image_to_window(all->data->mlx, all->data->win, \
		all->data->img, 0, 0);
	mlx_loop_hook(all->data->mlx, main_loop, all);
	mlx_hook(all->data->win, 2, 1L << 0, key_press, all);
	mlx_hook(all->data->win, 3, 1L<<1, key_release, all);
	mlx_hook(all->data->win, 17, 1L << 0, exit_cub, all);
	mlx_loop(all->data->mlx);
}

static void	check_args(int argc, t_all *all)
{
	if (argc < 2)
		printf("Need a map");
	else if (argc == 2)
		start_cub(all);
	else
	{
		init_player(all);
		sprites_init(all);
		all->data->mlx = mlx_init();
		all->data->img = mlx_new_image(all->data->mlx, all->params->width, \
			all->params->height);
		all->data->addr = mlx_get_data_addr(all->data->img, &all->data->bits_per_pixel, \
			&all->data->line_length, &all->data->endian);
		all->params->dist_to_wall = (double*)malloc(sizeof(double) * all->params->width + 10);
		if (!all->params->dist_to_wall)
			error_close(all, 8);
		buff_textures(all);
		cast_rays(all);
		draw_sprites(all);
		ft_cast_rays(all);
		draw_map(all);
		create_bmp(all);
	}
}

static void	check_arg_name(char **argv, t_all *all)
{
	char	**name;

	name = ft_split(argv[1], '.');
	if ((ft_strcmp(name[1], "cub") != 0))
		error_close(all, 1);
	if (argv[2])
	{
		if ((ft_strcmp(argv[2], "--save")) != 0)
			error_close(all, 11);
	}
	free_array(name);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_data		data;
	t_player	plr;
	t_all		all;

	all.plr = &plr;
	all.data = &data;
	all.params = &params;
	all.params->map = NULL;
	check_arg_name(argv, &all);
	read_map(argv[1], &all);
	check_args(argc, &all);
	return (0);
}

// косяки спрайтов
// норма
// сортировка
// мин значения