/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:48:59 by eblastoi          #+#    #+#             */
/*   Updated: 2021/04/28 17:13:43 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	*tmp;
	char		buff[BUFFER_SIZE + 1];

	if (!line || (BUFFER_SIZE <= 0) || (fd < 0))
		return (-1);
	buff[BUFFER_SIZE] = '\0';
	if (!tmp)
	{
		tmp = malloc(1);
		tmp[0] = 0;
	}
	tmp = check_read(fd, &tmp, buff, line);
	if (tmp == (char *)ERROR)
		return (-1);
	else if (tmp == (char *)NL)
		return (0);
	*ft_strchr(tmp, '\n') = '\0';
	*line = tmp;
	tmp = ft_strdup(ft_strchr(tmp, '\0') + 1);
	return (1);
}

char	*check_read(int fd, char **tmp, char *buff, char **line)
{
	int			res;
	char		*ptr;

	while (!(ft_strchr(*tmp, '\n')))
	{
		res = read(fd, buff, BUFFER_SIZE);
		if (res < 0)
			return ((char *)ERROR);
		if (res == 0)
		{
			*line = ft_strdup(*tmp);
			free(*tmp);
			*tmp = NULL;
			return ((char *)NL);
		}
		buff[res] = '\0';
		ptr = ft_strjoin(*tmp, buff);
		free(*tmp);
		*tmp = ptr;
	}
	return (*tmp);
}
