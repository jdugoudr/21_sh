/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_pad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 11:52:45 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/02 12:33:57 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int			buff_pad(t_pf_arg *arg, char c, int len)
{
	char	*str;

	if (len <= 0)
		return (0);
	if ((str = malloc((len + 1) * sizeof(char))) == NULL)
		return (-1);
	ft_memset(str, c, len);
	str[len] = '\0';
	buff_put(arg, str, len);
	free(str);
	return (len);
}
