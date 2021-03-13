/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:45:19 by eblastoi          #+#    #+#             */
/*   Updated: 2020/11/27 18:33:03 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dptr;
	const unsigned char	*sptr;

	dptr = dst;
	sptr = src;
	if (!dptr && !sptr)
		return (dst);
	if (dptr < sptr)
	{
		while (len)
		{
			*dptr++ = *sptr++;
			len--;
		}
	}
	else
	{
		while (len)
		{
			dptr[len - 1] = sptr[len - 1];
			len--;
		}
	}
	return (dst);
}
