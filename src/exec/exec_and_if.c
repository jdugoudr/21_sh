/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:58:18 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 19:23:41 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec_cmd.h"

/*
** Here we check the return of el->left.
** If it's 0 (execution succeed), we run el->right.
** Otherwise (execution failed), we return.
*/

int	exec_and_if(t_ast *el, t_ast *head, int ret)
{
	int	r;

	r = 0;
	if ((r = run_ast(el->left, head, ret)) == 0)
		return (run_ast(el->right, head, r));
	return (r);
}
