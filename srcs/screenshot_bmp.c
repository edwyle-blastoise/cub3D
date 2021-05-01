#include "cub3d.h"

static void	set_image(t_all *all, int fd)
{
	int	j;
	int	i;
	int	c;

	i = all->params->height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < all->params->width)
		{
			c = *(int *)((char *)all->data->addr + i \
				* all->data->line_length + j * 4);
			write(fd, &c, 4);
			j++;
		}
		i--;
	}
}

static void	set_header(t_all *all, int fd)
{
	int				size;
	unsigned char	header[54];

	size = 54 + (4 * all->params->width * all->params->height);
	ft_bzero(header, 54);
	header[0] = (unsigned char) 'B';
	header[1] = (unsigned char) 'M';
	header[2] = (unsigned char)size;
	header[3] = (unsigned char)(size >> 8);
	header[4] = (unsigned char)(size >> 16);
	header[5] = (unsigned char)(size >> 24);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	header[18] = (unsigned char)all->params->width;
	header[19] = (unsigned char)(all->params->width >> 8);
	header[20] = (unsigned char)(all->params->width >> 16);
	header[21] = (unsigned char)(all->params->width >> 24);
	header[22] = (unsigned char)all->params->height;
	header[23] = (unsigned char)(all->params->height >> 8);
	header[24] = (unsigned char)(all->params->height >> 16);
	header[25] = (unsigned char)(all->params->height >> 24);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(fd, header, 54);
}

int	create_bmp(t_all *all)
{
	int	fd;

	fd = open("Screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		error_close(all, 10);
	set_header(all, fd);
	set_image(all, fd);
	close(fd);
	exit(0);
}
