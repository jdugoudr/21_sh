/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwa <marwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:52:56 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/17 20:31:59 by marwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** '0' flag results in undefined behavior.
*/

int			handler_char(t_pf_arg *arg, va_list ap)
{
	char			value;
	int				ret;
	char			c;

	ret = 0;
	if (arg->type != 'c')
		value = arg->type;
	else
		value = (unsigned char)va_arg(ap, int);
	if (arg->flags & MINUS_F)
	{
		ret += buff_put(arg, &value, 1) + buff_pad(arg, ' ', arg->width - 1);
		return (ret);
	}
	c = (arg->flags & ZERO_F ? '0' : ' ');
	ret += buff_pad(arg, c, arg->width - 1) + buff_put(arg, &value, 1);
	return (ret);
}
