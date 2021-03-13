/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 15:18:14 by eblastoi          #+#    #+#             */
/*   Updated: 2020/11/27 18:57:35 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_rows(char const *s, char c)
{
	size_t	i;
	size_t	rows;

	i = 0;
	rows = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			rows++;
		i++;
	}
	return (rows);
}

static	size_t	count_length(char const *s, size_t i, char c)
{
	size_t	col;

	col = 0;
	if (s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
		col++;
		i++;
	}
	return (col);
}

static	void	ft_free(char **res, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(res[i]);
		i++;
	}
	free(res);
}

static	char	**fill_arr(char const *s, char c, size_t rows)
{
	char	**arr;
	size_t	len;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	arr = (char**)malloc((rows + 1) * sizeof(char*));
	if (!arr)
		return (NULL);
	arr[rows] = NULL;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			len = count_length(s, i, c);
			if (!(arr[j] = ft_substr(s, i, len)))
				ft_free(arr, j);
			j++;
			i = i + len;
		}
	}
	return (arr);
}

char			**ft_split(char const *s, char c)
{
	char		**result;
	size_t		rows;

	if (!s)
		return (NULL);
	rows = count_rows(s, c);
	result = fill_arr(s, c, rows);
	return (result);
}
