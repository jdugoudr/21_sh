/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_sharp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:07:12 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/02 12:34:44 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

char	*process_sharp(t_pf_arg *arg, char *str)
{
	char	*ret;

	if (arg->type == 'o' && str[0] != '0')
	{
		ret = ft_strjoin("0", str, 2);
		return (ret);
	}
	if (arg->type == 'x' && ft_strcmp(str, "0") && str[0])
	{
		ret = ft_strjoin("0x", str, 2);
		return (ret);
	}
	if (arg->type == 'X' && ft_strcmp(str, "0") && str[0])
	{
		ret = ft_strjoin("0X", str, 2);
		return (ret);
	}
	if (arg->type == 'f' && arg->precision == 0)
	{
		ret = ft_strjoin(str, ".", 1);
		return (ret);
	}
	return (str);
}
