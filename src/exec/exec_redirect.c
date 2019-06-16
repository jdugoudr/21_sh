/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:03:36 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 19:25:43 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"
#include "sh_error.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	exec_redirect(t_ast *el, t_ast *head, int ret)
{
	return (run_ast(el->left, head, ret));
}

int	find_and_exec_redirect(t_ast *el, t_fd **fd_lst)
{
	int r;

	r = 0;
	if (el->type & (GREAT_TOK))
		r = exec_out_redir(el, fd_lst, O_WRONLY | O_CREAT
			| O_TRUNC, STDOUT_FILENO);
	else if (el->type & DGREAT_TOK)
		r = exec_out_redir(el, fd_lst, O_WRONLY | O_CREAT
			| O_APPEND, STDOUT_FILENO);
	else if (el->type & (GREAT_FD_TOK | DGREAT_FD_TOK))
		r = exec_out_redir(el, fd_lst, 0, STDOUT_FILENO);
	else if (el->type & LESS_TOK)
		r = exec_in_redir(el, fd_lst, O_RDONLY, STDIN_FILENO);
	else if (el->type & DLESS_TOK)
		r = exec_in_redir(el, fd_lst, O_RDONLY, STDIN_FILENO);
	else if (el->type & LESS_FD_TOK)
		r = exec_in_redir(el, fd_lst, 0, STDIN_FILENO);
	else
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
	return (r);
}
