/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:58:18 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/08 20:23:45 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec_cmd.h"

/*
** Here we check the return of el->left.
** If it's 0 (execution succeed), we run el->right.
** Otherwise (execution failed), we return.
*/

int	exec_and_if(t_ast *el, t_ast *head)
{
	int	r;

	r = 0;
	if ((r = run_ast(el->left, head)) == 0)
		return (run_ast(el->right, head));
	return (r);
}
