/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:09:52 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/16 21:22:07 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** no length modifier : 0
** hh: 1, h: 2, 	ll: 3, l: 4, 	L: 5, 	z: 6, 	j: 7
*/

void	set_length(t_pf_arg *arg, char length)
{
	int		value;

	value = 0;
	if (length == 'h')
		value = 2;
	else if (length == 'l')
		value = 4;
	else if (length == 'L')
		value = 5;
	else if (length == 'z')
		value = 6;
	else if (length == 'j')
		value = 7;
	if (value == 2 && arg->length == 2)
		arg->length = 1;
	else if (value == 4 && arg->length == 4)
		arg->length = 3;
	else
		arg->length = (int)ft_max(value, arg->length);
}
