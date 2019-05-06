/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_put.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 11:53:05 by mdaoud            #+#    #+#             */
/*   Updated: 2019/01/05 13:36:01 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			buff_put(t_pf_arg *arg, char *c, size_t len)
{
	int		i;
	int		div;

	div = len / PF_BUFF_SIZE;
	i = 0;
	if ((int)len >= PF_BUFF_SIZE - arg->it)
	{
		buff_flush(arg);
		while (i < div)
		{
			ft_memcpy(arg->buff, c + (i * PF_BUFF_SIZE), PF_BUFF_SIZE);
			arg->it = PF_BUFF_SIZE;
			buff_flush(arg);
			i++;
		}
	}
	ft_memcpy(arg->buff + arg->it, c + (i * PF_BUFF_SIZE), len % PF_BUFF_SIZE);
	arg->it += len % PF_BUFF_SIZE;
	arg->buff[arg->it] = '\0';
	return (len);
}
