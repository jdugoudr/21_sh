/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:21:24 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/16 16:32:03 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*convert(unsigned int n, int len, int neg)
{
	char	*retval;
	int		i;
	int		size;

	size = len + neg + 1;
	if (!(retval = malloc(size * sizeof(char))))
		return (NULL);
	retval[size - 1] = '\0';
	i = len - 1;
	if (neg)
	{
		retval[0] = '-';
		i = len;
	}
	while (n >= 10)
	{
		retval[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	retval[i] = n + '0';
	return (retval);
}

/*
** INT_MIN: -2147483648
** INT_MAX: 2147483647
*/

char			*ft_itoa(int n)
{
	int				neg;
	int				len;
	unsigned int	nbr;

	neg = 0;
	len = 0;
	nbr = n;
	if (n < 0)
	{
		neg = 1;
		nbr = -n;
	}
	while (nbr)
	{
		len++;
		nbr /= 10;
	}
	nbr = (n < 0 ? -n : n);
	len = (n == 0 ? 1 : len);
	return (convert(nbr, len, neg));
}
