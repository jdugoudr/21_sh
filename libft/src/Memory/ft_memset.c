/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:59:09 by mdaoud            #+#    #+#             */
/*   Updated: 2019/01/05 13:38:16 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void		*ft_memset(void *ptr, int c, size_t n)
{
	unsigned char	*temp;

	temp = ptr;
	while (n)
	{
		*temp = (unsigned char)c;
		temp++;
		n--;
	}
	return (ptr);
}
