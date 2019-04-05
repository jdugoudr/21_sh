/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 09:37:15 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/05 14:51:01 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_ast.h"
#include "exec_cmd.h"

static int	do_run_after(t_ast *el, int ret)
{
	int	do_it;

	do_it = 0;
	if (el->type & AND_IF)
	{
		if (ret)
			return (0);
		return (1);
	}
	else
		return (ret);
}

static int	loop_run(t_ast *el)
{
	int	ret;
	int	do_it;

	do_it = 1;
	ret = 0;
	if ( el->f_exec)
			ret = el->f_exec(el, ret);
	if (el->left)
		ret = loop_run(el->left);
	if (el->type & RUN_AFTER)
		do_it = do_run_after(el, ret);
	if (do_it && el->right && el->level_prior > LEVEL_REDI)
		ret = loop_run(el->right);
	return (ret);
}

int	run_ast(t_ast *root)
{
	int	ret;

	if (!root)
		return (0);
	ret = loop_run(root);
	return (ret);
}
