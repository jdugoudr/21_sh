/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwa <marwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:04:24 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/17 20:31:59 by marwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Precision specifies the maximum number of bytes to be written.
** '0' flag results in undefined behavior.
*/

static int	parse_str(t_pf_arg *arg, char *str)
{
	int		ret;
	int		len;
	int		pad;

	ret = 0;
	if (arg->flags & DOT_F)
		len = ft_min((int)ft_strlen(str), arg->precision);
	else
		len = (int)ft_strlen(str);
	pad = arg->width - len;
	if (arg->flags & MINUS_F)
	{
		ret += buff_put(arg, str, len) + buff_pad(arg, ' ', pad);
		return (ret);
	}
	if (arg->flags & ZERO_F)
		ret += buff_pad(arg, '0', pad) + buff_put(arg, str, len);
	else
		ret += buff_pad(arg, ' ', pad) + buff_put(arg, str, len);
	return (ret);
}

int			handler_string(t_pf_arg *arg, va_list ap)
{
	char	*str;
	int		ret;
	int		free_flag;

	ret = 0;
	free_flag = 0;
	str = (char *)va_arg(ap, char *);
	if (str == NULL)
	{
		str = ft_strdup("(null)");
		free_flag = 1;
	}
	ret = parse_str(arg, str);
	if (free_flag)
		free(str);
	return (ret);
}
