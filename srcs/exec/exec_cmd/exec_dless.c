/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dless.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:01:58 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/06 17:07:30 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

/*
** Here we execute a heredocument
**
*/

int	exec_dless(t_ast *el)
{
	(void)el;
	ft_printf("execution of <<\n");////////////
	return (0);
}
