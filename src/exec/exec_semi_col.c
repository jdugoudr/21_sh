/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_semi_col.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:53:20 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/02 18:43:39 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"

/*
** Here we execute el->left then el->right.
** Whatever the result of el->left.
*/

int	exec_semi_col(t_ast *el, t_shell *shell, t_ast *head)
{
	run_ast(el->left, shell, head);
	return (run_ast(el->right, shell, head));
}
