/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or_if.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:01:18 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/07 10:56:48 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_ast.h"
#include "exec_cmd.h"

/*
** Here we check the return of el->left.
** If it's 0 (execution succeed), we return.
** Otherwise (execution failed), we run el->right.
*/

int	exec_or_if(t_ast *el)
{
	int	r;

	r = run_ast(el->left);
	if (r)
		return (run_ast(el->right));
	return (r);
}
