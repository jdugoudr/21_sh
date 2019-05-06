/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_plus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:06:02 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/16 16:06:16 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*process_plus(t_pf_arg *arg, char *str)
{
	char	*ret;

	if (ft_strchr("dif", arg->type) && str[0] != '-')
	{
		ret = ft_strjoin("+", str, 2);
		return (ret);
	}
	return (str);
}
