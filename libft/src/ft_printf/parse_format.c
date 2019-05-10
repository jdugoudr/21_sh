/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:04:56 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 17:08:32 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Reset the static structure.
*/

static void		reset_arg(t_pf_arg *arg, int *percent)
{
	arg->type = ' ';
	arg->flags = 0;
	arg->width = 0;
	arg->precision = 0;
	arg->length = 0;
	arg->stars = 0;
	*percent = 0;
}

static void		process_number(t_pf_arg *arg, char *num)
{
	int		value;

	if (*num == '0' && *(num - 1) != '.')
	{
		arg->flags |= ZERO_F;
		return ;
	}
	value = ft_atoi(num);
	if (*(num - 1) == '.')
		arg->precision = value;
	else
		arg->width = value;
	if (arg->precision < 0)
		arg->flags &= ~DOT_F;
	if (arg->width < 0)
	{
		arg->flags |= MINUS_F;
		arg->width *= -1;
	}
}

int				parse_format(int fd, char *c, va_list ap, int *percent)
{
	static t_pf_arg arg = {' ', {0}, 0, 0, 0, 0, 0, 0, 0};
	int				ret;

	ret = 0;
	arg.fd = fd;
	if (c == NULL)
		buff_flush(&arg);
	else if (*percent == 0 && *c != '%')
		ret += buff_put(&arg, c, 1);
	else if (*percent == 0 && *c == '%')
		*percent = 1;
	else if (ft_strchr("#- +*.", *c))
		set_flag(&arg, c, ap);
	else if (ft_strchr("jhlLz", *c))
		set_length(&arg, *c);
	else if (*c >= '0' && *c <= '9')
		process_number(&arg, c);
	else
	{
		ret += dispatch_handlers(&arg, *c, ap);
		reset_arg(&arg, percent);
	}
	return (ret);
}
