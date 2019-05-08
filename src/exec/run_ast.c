/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 09:37:15 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/08 19:25:55 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec_cmd.h"
#include "sh_error.h"

int	run_ast(t_ast *el, t_shell *shell, t_ast *head)
{
	(void)shell;
	if (!el)
		return (0);
	if (el->f_exec == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (el->f_exec(el, shell, head));
}
