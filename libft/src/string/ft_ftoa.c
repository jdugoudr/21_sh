/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:21:24 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/16 16:32:30 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*pad(char *str, int length)
{
	char	*pad;

	if (str == NULL || length <= 1)
		return (str);
	if ((pad = malloc((length - 1) * sizeof(char))) == NULL)
		return (NULL);
	ft_memset(pad, '0', length - 1);
	pad[length - 1] = '\0';
	return (ft_strjoin(str, pad, 2));
}

char		*ft_ftoa(long double nbr, int precision)
{
	long long				ipart;
	long double				fpart;
	long double				temp;
	int						last_dec;
	char					*result;

	ipart = (long long)nbr;
	precision = (precision < 0 ? 6 : precision);
	nbr = (nbr >= 0 ? nbr : -nbr);
	temp = (ipart >= 0 ? (long double)ipart : (long double)ipart * -1);
	fpart = nbr - temp;
	temp = ft_pow(10, precision) * fpart;
	fpart = ft_pow(10, precision) * fpart;
	last_dec = (long long)(fpart * 10) % 10;
	if (last_dec >= 5 && precision != 0)
		temp += 1;
	else if (last_dec >= 5 && precision == 0)
		ipart = (ipart >= 0 ? ipart + 1 : ipart - 1);
	result = ft_ltoa(ipart);
	if (precision == 0)
		return (result);
	result = ft_strjoin(result, ".", 1);
	result = ft_strjoin(result, ft_ltoa(temp), 3);
	return (temp == 0 ? pad(result, precision) : result);
}
