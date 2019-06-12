/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwa <marwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 12:52:04 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/23 18:00:31 by marwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *ptr, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)ptr == (unsigned char)c)
			return ((void *)ptr);
		ptr = (unsigned char *)ptr + 1;
	}
	return (NULL);
}
