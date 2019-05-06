/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:59:19 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/02 12:34:30 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

/*
** Following flags are ignored: ' ', '+'
*/

static void		process_flags(t_pf_arg *arg)
{
	int flags;

	flags = arg->flags;
	flags &= ~SPACE_F;
	flags &= ~PLUS_F;
	if ((flags & ZERO_F) && (flags & DOT_F))
		flags &= ~ZERO_F;
	if ((flags & ZERO_F) && (flags & MINUS_F))
		flags &= ~ZERO_F;
	arg->flags = flags;
}

static int		get_prefix(char type, char *str, int len)
{
	if (type == 'd' || type == 'i')
		return ((str[0] == ' ') || (str[0] == '-') || (str[0] == '+'));
	else if (type == 'x' || type == 'X')
		if (len >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
			return (2);
	return (0);
}

static int		parse_str(t_pf_arg *arg, char *str)
{
	int		ret;
	int		prefix;
	int		pad;
	int		len;

	if (str == NULL)
		return (-1);
	process_flags(arg);
	ret = 0;
	if (arg->flags & SHARP_F)
		str = process_sharp(arg, str);
	len = (int)ft_strlen(str);
	prefix = get_prefix(arg->type, str, len);
	if (arg->flags & ZERO_F)
		return (ret + process_zero(arg, str));
	pad = arg->width - ft_max(arg->precision + prefix, len);
	if (arg->flags & MINUS_F)
	{
		ret = ret + process_precision(arg, str, len);
		free(str);
		return (ret + buff_pad(arg, ' ', pad));
	}
	ret = ret + buff_pad(arg, ' ', pad) + process_precision(arg, str, len);
	free(str);
	return (ret);
}

static char		*dispatch_unsigned(t_pf_arg *arg, unsigned long long value)
{
	char	*str;

	str = NULL;
	if (arg->type == 'b')
		str = ft_ltoa_base(value, 2, 0);
	else if (arg->type == 'o')
		str = ft_ltoa_base(value, 8, 0);
	else if (arg->type == 'u')
		str = ft_ultoa(value);
	else if (arg->type == 'x')
		str = ft_ltoa_base(value, 16, 0);
	else if (arg->type == 'X')
		str = ft_ltoa_base(value, 16, 1);
	return (str);
}

int				handler_unsigned(t_pf_arg *arg, va_list ap)
{
	unsigned long long	value;
	char				*str;

	str = NULL;
	if (arg->length == 1)
		value = (unsigned char)va_arg(ap, int);
	else if (arg->length == 2)
		value = (unsigned short)va_arg(ap, int);
	else if (arg->length == 3)
		value = (unsigned long long)va_arg(ap, unsigned long long);
	else if (arg->length == 4)
		value = (unsigned long)va_arg(ap, unsigned long);
	else if (arg->length == 6)
		value = (size_t)va_arg(ap, size_t);
	else if (arg->length == 7)
		value = (uintmax_t)va_arg(ap, uintmax_t);
	else
		value = (unsigned int)va_arg(ap, unsigned int);
	if ((arg->flags & DOT_F) && arg->precision == 0 && value == 0)
		str = ft_strdup("");
	else
		str = dispatch_unsigned(arg, value);
	return (parse_str(arg, str));
}
