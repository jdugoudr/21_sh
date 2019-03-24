/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:25:43 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/02/01 14:36:17 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(size_t *a, size_t *b)
{
	size_t	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
