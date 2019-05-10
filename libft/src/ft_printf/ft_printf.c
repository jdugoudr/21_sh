/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:52:43 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 17:05:22 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init(int *ret, int *percent, int *i)
{
	*ret = 0;
	*percent = 0;
	*i = 0;
}

int			ft_printf(const char *format, ...)
{
	int			i;
	int			ret;
	int			percent;
	va_list		ap;

	va_start(ap, format);
	init(&ret, &percent, &i);
	while (format[i])
	{
		ret += parse_format(STDOUT_FILENO, (char *)format + i, ap, &percent);
		if (format[i] >= '1' && format[i] <= '9' && percent == 1)
		{
			while (format[i] && format[i] >= '0' && format[i] <= '9')
				i++;
			continue ;
		}
		i++;
	}
	parse_format(STDOUT_FILENO, NULL, ap, NULL);
	va_end(ap);
	return (ret);
}
