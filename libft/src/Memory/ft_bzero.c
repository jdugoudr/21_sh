/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:31:33 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/10 13:56:45 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Replace sizeof(size_t) and size_t with uni64_t for more optimisation
*/

void		ft_bzero(void *ptr, size_t n)
{
	while (n / sizeof(size_t))
	{
		*(size_t *)ptr = 0;
		ptr = (size_t *)ptr + 1;
		n -= sizeof(size_t);
	}
	while (n--)
	{
		*(char *)ptr = 0;
		ptr = (char *)ptr + 1;
	}
}
