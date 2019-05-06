/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 17:12:06 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/17 16:26:11 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr(int n)
{
	int				buff[15];
	int				i;
	unsigned int	nbr;

	i = 0;
	nbr = n;
	if (n < 0)
	{
		ft_putchar('-');
		nbr = -n;
	}
	while (nbr > 10)
	{
		buff[i++] = nbr % 10;
		nbr /= 10;
	}
	buff[i++] = nbr;
	while (--i >= 0)
		ft_putchar(buff[i] + '0');
}
