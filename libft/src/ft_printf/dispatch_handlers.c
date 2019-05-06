/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwa <marwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:52:19 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/17 19:16:14 by marwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		dispatch_handlers(t_pf_arg *arg, char type, va_list ap)
{
	int		ret;

	ret = -1;
	arg->type = type;
	if (ft_strchr("di", type))
		ret = handler_int(arg, ap);
	else if (type == 's')
		ret = handler_string(arg, ap);
	else if (ft_strchr("bouxX", type))
		ret = handler_unsigned(arg, ap);
	else if (arg->type == 'f')
		ret = handler_float(arg, ap);
	else if (arg->type == 'p')
		ret = handler_pointer(arg, ap);
	else
		ret = handler_char(arg, ap);
	return (ret);
}
