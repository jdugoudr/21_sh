/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_semi_col.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:53:20 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 19:43:30 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"

/*
** Here we execute el->left then el->right.
** Whatever the result of el->left.
*/

int	exec_semi_col(t_ast *el, t_ast *head, int ret)
{
	int	r;

	r = run_ast(el->left, head, ret);
	if (el->right == NULL)
		return (r);
	return (run_ast(el->right, head, r));
}
