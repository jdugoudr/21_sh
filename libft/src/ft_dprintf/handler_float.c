/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:53:43 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/02 12:34:19 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

/*
** 0 flag is ignored with '-'.
** ' ' flag is ignored with '+'.
*/

static void		process_flags(t_pf_arg *arg)
{
	int flags;

	flags = arg->flags;
	if (flags & ZERO_F && flags & MINUS_F)
		flags &= ~ZERO_F;
	if (flags & SPACE_F && flags & PLUS_F)
		flags &= ~SPACE_F;
	arg->flags = flags;
}

static int		parse_buff(t_pf_arg *arg, char *str)
{
	int		ret;
	int		sign;
	int		pad;
	int		len;

	process_flags(arg);
	ret = 0;
	if (arg->flags & SPACE_F)
		str = process_space(arg, str);
	if (arg->flags & PLUS_F)
		str = process_plus(arg, str);
	if (arg->flags & SHARP_F)
		str = process_sharp(arg, str);
	len = (int)ft_strlen(str);
	sign = ((str[0] == ' ') || (str[0] == '-') || (str[0] == '+'));
	if (arg->flags & ZERO_F)
		return (ret + process_zero(arg, str));
	pad = arg->width - (arg->precision >= len ? arg->precision + sign : len);
	if (arg->flags & MINUS_F)
		ret += buff_put(arg, str, len) + buff_pad(arg, ' ', pad);
	else
		ret += buff_pad(arg, ' ', pad) + buff_put(arg, str, len);
	free(str);
	return (ret);
}

int				handler_float(t_pf_arg *arg, va_list ap)
{
	long double		value;
	char			*str;

	value = 0.0;
	if (arg->length == 0 || arg->length == 4)
		value = va_arg(ap, double);
	else if (arg->length == 5)
		value = va_arg(ap, long double);
	if ((arg->flags & DOT_F) == 0)
	{
		arg->flags = arg->flags | DOT_F;
		arg->precision = 6;
	}
	str = ft_ftoa(value, arg->precision);
	if (str == NULL)
		return (-1);
	return (parse_buff(arg, str));
}
