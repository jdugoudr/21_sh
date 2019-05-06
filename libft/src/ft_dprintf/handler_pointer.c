/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:58:11 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/02 12:34:26 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static char	*get_str(t_pf_arg *arg, long value)
{
	char	*str;

	str = NULL;
	if (value == 0 && (arg->flags & DOT_F) && arg->precision == 0)
		str = ft_strdup("");
	else
		str = ft_ltoa_base(value, 16, 0);
	str = ft_strjoin("0x", str, 2);
	return (str);
}

int			handler_pointer(t_pf_arg *arg, va_list ap)
{
	long	value;
	char	*str;
	int		len;
	int		pad;
	int		ret;

	ret = 0;
	value = (long)va_arg(ap, long);
	str = get_str(arg, value);
	len = ft_strlen(str);
	if (arg->flags & ZERO_F)
		return (process_zero(arg, str));
	pad = arg->width - ft_max(arg->precision + 2, len);
	if (arg->flags & MINUS_F)
	{
		ret = ret + process_precision(arg, str, len) + buff_pad(arg, ' ', pad);
		free(str);
		return (ret);
	}
	ret = ret + buff_pad(arg, ' ', pad) + process_precision(arg, str, len);
	free(str);
	return (ret);
}
