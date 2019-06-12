/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:21:24 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/16 16:33:12 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*convert(unsigned long long n, int len, int neg)
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
** LONG_MAX: 9223372036854775807
** LONG_MIN: -9223372036854775808
*/

char			*ft_ltoa(long long n)
{
	int					neg;
	int					len;
	unsigned long long	nbr;

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
