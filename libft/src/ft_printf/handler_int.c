/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwa <marwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:55:09 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/26 18:29:28 by marwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Remove the ignored flags in the cases shown below
*/

static void		process_flags(t_pf_arg *arg)
{
	int flags;

	flags = arg->flags;
	if (flags & ZERO_F && flags & DOT_F)
		flags &= ~ZERO_F;
	if (flags & ZERO_F && flags & MINUS_F)
		flags &= ~ZERO_F;
	if (flags & SPACE_F && flags & PLUS_F)
		flags &= ~SPACE_F;
	arg->flags = flags;
}

/*
** printf("#d", 42): Warning # used with %d.
** printf("%0.3d", 42): 0 flag ignored with '.' flag.
** printf("%-05d", 42): 0 flag is ignored with '-'.
** printf("% +5d", 42): ' ' flag is ignored with '+'.
** printf("%.0d", 0): if both precision and value is 0, nothing is printed.
** printf("%.5d", 42): precision is taken as minimum number to be printed.
** printf("%0d", 42): zero flag has no effect if no minimum width is specified.
** printf("%05d", 42): pad with 0 until minimum width is reached.
*/

static int		parse_str(t_pf_arg *arg, char *str)
{
	int		ret;
	int		sign;
	int		pad;
	int		len;

	if (str == NULL)
		return (-1);
	process_flags(arg);
	ret = 0;
	if (arg->flags & SPACE_F)
		str = process_space(arg, str);
	if (arg->flags & PLUS_F)
		str = process_plus(arg, str);
	len = (int)ft_strlen(str);
	sign = ((str[0] == ' ') || (str[0] == '-') || (str[0] == '+'));
	if (arg->flags & ZERO_F)
		return (ret + process_zero(arg, str));
	pad = arg->width - (arg->precision >= len ? arg->precision + sign : len);
	if (arg->flags & MINUS_F)
		ret += process_precision(arg, str, len) + buff_pad(arg, ' ', pad);
	else
		ret += buff_pad(arg, ' ', pad) + process_precision(arg, str, len);
	free(str);
	return (ret);
}

int				handler_int(t_pf_arg *arg, va_list ap)
{
	long long	value;
	char		*str;

	if (arg->length == 0)
		value = va_arg(ap, int);
	else if (arg->length == 1)
		value = (char)va_arg(ap, int);
	else if (arg->length == 2)
		value = (short)va_arg(ap, int);
	else if (arg->length == 3)
		value = va_arg(ap, long long);
	else if (arg->length == 4)
		value = (long)va_arg(ap, long);
	else if (arg->length == 5)
		value = va_arg(ap, long long);
	else if (arg->length == 6)
		value = (size_t)va_arg(ap, size_t);
	else
		value = (intmax_t)va_arg(ap, intmax_t);
	if ((arg->flags & DOT_F) && arg->precision == 0 && value == 0)
		str = ft_strdup("");
	else
		str = ft_ltoa(value);
	return (parse_str(arg, str));
}
