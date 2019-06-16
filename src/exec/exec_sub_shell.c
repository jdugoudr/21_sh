/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:07:12 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 19:29:46 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"
#include "sh_error.h"
#include "editor.h"
#include "shell21.h"
#include "libft.h"
#include <sys/types.h>

/*
** Here we execute a subshell.
** We just have to call the function run_ast with sub_tree of token structur
*/

int	exec_sub_shell(t_ast *el, t_ast *head, int ret)
{
	pid_t	child;
	int		r;

	r = 0;
	child = fork();
	if (child == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	else if (child == 0)
	{
		r = run_ast(el->ast_sub, head, ret);
		free_shell();
		free_editor();
		del_ast(&head);
		if (r)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(child, &r, 0);
	return (r);
}
