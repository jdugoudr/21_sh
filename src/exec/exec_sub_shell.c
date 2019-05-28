/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:07:12 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/28 10:46:38 by jdugoudr         ###   ########.fr       */
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

int	exec_sub_shell(t_ast *el, t_ast *head)
{
	pid_t	child;
	int		ret;

	ret = 0;
	child = fork();
	if (child == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	else if (child == 0)
	{
		ret = run_ast(el->ast_sub, head);
		free_shell();
		free_editor();
		del_ast(&head);
		if (ret)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(child, &ret, 0);
	return (ret);
}
