/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 09:37:15 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/06 17:09:34 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_ast.h"
#include "exec_cmd.h"
#include "sh_error.h"

int	run_ast(t_ast *el)
{
	if (!el)
		return (0);
	if (el->f_exec == NULL)
	{
		ft_fprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (el->f_exec(el));
}
