/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:57:30 by eblastoi          #+#    #+#             */
/*   Updated: 2020/11/27 18:52:02 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[len - 1] && ft_strchr(set, s1[len - 1]))
		len--;
	if (i >= len)
		return (ft_strdup(""));
	result = (char*)malloc(sizeof(char) * ((len - i) + 1));
	if (!result)
		return (NULL);
	while (i < len)
		result[j++] = s1[i++];
	result[j] = '\0';
	return (result);
}
