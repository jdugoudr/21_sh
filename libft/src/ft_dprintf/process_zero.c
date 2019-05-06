/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_zero.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:08:07 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/02 12:34:48 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int		process_zero(t_pf_arg *arg, char *str)
{
	int		ret;
	int		prefix;
	int		pad;
	int		len;

	ret = 0;
	prefix = 0;
	len = (int)ft_strlen(str);
	if (ft_strchr("bdiuoxXfp", arg->type))
	{
		if (len >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
			prefix = 2;
		else if (str[0] == ' ' || str[0] == '+' || str[0] == '-')
			prefix = 1;
		pad = arg->width - len;
		if (prefix != 0)
			ret += buff_put(arg, str, prefix);
		ret += buff_pad(arg, '0', pad);
		ret += buff_put(arg, str + prefix, len - prefix);
		free(str);
	}
	return (ret);
}
