/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:06:24 by eblastoi          #+#    #+#             */
/*   Updated: 2020/11/24 14:38:38 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int		i;
	unsigned char		cptr;
	unsigned char		*dptr;
	const unsigned char	*sptr;

	cptr = c;
	dptr = dst;
	sptr = src;
	i = 0;
	while (i < n)
	{
		dptr[i] = sptr[i];
		if (dptr[i] == cptr)
		{
			return (&dptr[i + 1]);
		}
		i++;
	}
	return (NULL);
}
