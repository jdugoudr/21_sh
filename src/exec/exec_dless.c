/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dless.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:01:58 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/02 17:51:16 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

/*
** Here we execute a heredocument
**
*/

int	exec_dless(t_ast *el, t_shell *shell, t_ast *head)
{
	(void)el;
	(void)shell;
	(void)head;
	ft_printf("execution of <<\n");////////////
	return (0);
}
