/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:19:28 by eblastoi          #+#    #+#             */
/*   Updated: 2020/11/27 18:26:47 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dptr;
	const unsigned char	*sptr;

	dptr = dst;
	sptr = src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		dptr[i] = sptr[i];
		i++;
	}
	return (dst);
}
