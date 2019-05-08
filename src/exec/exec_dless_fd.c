/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dless_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:04:37 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/08 20:36:43 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

/*
** Here we execute a heredocument
**
*/

int	exec_dless_fd(t_ast *el, t_ast *head)
{
	(void)el;
	(void)head;
	ft_printf("execution of <<&\n");////////////
	return (0);
}
