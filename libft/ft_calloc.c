/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:31:53 by eblastoi          #+#    #+#             */
/*   Updated: 2020/11/27 18:48:25 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	*p_memory;

	p_memory = (size_t*)malloc(count * size);
	if (p_memory)
		ft_bzero(p_memory, (count * size));
	return (p_memory);
}
