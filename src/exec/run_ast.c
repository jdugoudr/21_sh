/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 09:37:15 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/21 10:16:22 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec_cmd.h"
#include "sh_error.h"

int	run_ast(t_ast *el, t_ast *head)
{
	if (!el)
		return (0);
	if (el->f_exec == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (el->f_exec(el, head));
}
