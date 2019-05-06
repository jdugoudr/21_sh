/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 10:59:40 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/02 19:30:17 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"
#include "sh_error.h"
#include <sys/types.h>
#include <sys/wait.h>//linux

/*
** Here we redirect el->left output in el->right input.
** The child process execute redirection and run el->left then
** EXIT and not return to kill himself.
** The parent process wait and run and return el->right.
** We have to fork two times, because if not, the redirection
** of the input in father process will still be effective when we return.
*/

static void	free_exit(int r, t_shell *shell, t_ast *head)
{
	(void)shell;
	(void)head;
	//free_shell(shell);
	//free_editor(editor);
	del_ast(&head);
	exit(r);
}

static int	do_pipe(t_ast *el, int *pdes, t_shell *shell, t_ast *head)
{
	int		r;
	pid_t	child;

	r = 0;
	child = fork();
	if (child == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	if (child == 0)
	{
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		close(pdes[READ_END]);
		r = run_ast(el->left, shell, head);
		free_exit(r, shell, head);

	}
	dup2(pdes[READ_END], STDIN_FILENO);
	close(pdes[WRITE_END]);
	waitpid(child, &r, 0);
	r = run_ast(el->right, shell, head);
	return (r);
}

int	exec_pipe(t_ast *el, t_shell *shell, t_ast *head)
{
	int		pdes[2];
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
		if (pipe(pdes) == -1)
		{
			ft_dprintf(STDERR_FILENO, INTERN_ERR);
			return (1);
		}
		r = do_pipe(el, pdes, shell, head);
		free_exit(r, shell, head);
	}
	else
		waitpid(child, &r, 0);
	return (r);
}
