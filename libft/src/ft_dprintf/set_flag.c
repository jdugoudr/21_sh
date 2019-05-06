/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:09:41 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/02 12:34:49 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	process_star(t_pf_arg *arg, char *c, va_list ap)
{
	if (*(c - 1) == '.')
	{
		arg->precision = va_arg(ap, int);
		if (arg->precision < 0)
			arg->flags &= ~DOT_F;
		return ;
	}
	arg->width = va_arg(ap, int);
	if (arg->width < 0)
	{
		arg->flags |= MINUS_F;
		arg->width *= -1;
	}
	return ;
}

void		set_flag(t_pf_arg *arg, char *c, va_list ap)
{
	if (*c == '#')
		arg->flags |= SHARP_F;
	else if (*c == '-')
		arg->flags |= MINUS_F;
	else if (*c == ' ')
		arg->flags |= SPACE_F;
	else if (*c == '+')
		arg->flags |= PLUS_F;
	else if (*c == '.')
	{
		arg->flags |= DOT_F;
		if (*(c + 1) < '0' || *(c + 1) > '9')
			arg->precision = 0;
	}
	else if (*c == '*')
		process_star(arg, c, ap);
}
