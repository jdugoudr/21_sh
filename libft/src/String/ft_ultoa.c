/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:21:24 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/16 19:11:59 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ULONG_MAX: 18446744073709551615.
** ULONG_MAX takes 20 places, so we malloc 20+1 for '\0'.
*/

char			*ft_ultoa(unsigned long long nbr)
{
	int					i;
	int					len;
	unsigned long long	n;
	char				*result;

	if ((result = malloc(21 * sizeof(char))) == NULL)
		return (NULL);
	len = 0;
	n = nbr;
	while (n)
	{
		len++;
		n /= 10;
	}
	len = (len == 0 ? 1 : len);
	i = len - 1;
	result[len] = '\0';
	while (nbr >= 10)
	{
		result[i--] = nbr % 10 + '0';
		nbr /= 10;
	}
	result[i] = nbr + '0';
	return (ft_strdup_free(result));
}
