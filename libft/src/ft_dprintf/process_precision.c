/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_precision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:06:32 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/02 12:34:42 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int		process_precision(t_pf_arg *arg, char *str, int len)
{
	int		prefix;
	int		pad;
	int		ret;

	ret = 0;
	prefix = 0;
	if (len >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		prefix = 2;
	else if (str[0] == ' ' || str[0] == '-' || str[0] == '+')
		prefix = 1;
	pad = arg->precision - len + prefix;
	if (prefix != 0)
		ret = ret + buff_put(arg, str, prefix);
	ret += buff_pad(arg, '0', pad) + buff_put(arg, str + prefix, len - prefix);
	return (ret);
}
