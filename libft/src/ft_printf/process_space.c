/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:07:53 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/16 16:08:02 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*process_space(t_pf_arg *arg, char *str)
{
	char	*ret;

	if (ft_strchr("dif", arg->type) && str[0] != '-')
	{
		ret = ft_strjoin(" ", str, 2);
		return (ret);
	}
	return (str);
}
