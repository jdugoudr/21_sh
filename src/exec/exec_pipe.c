/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 10:59:40 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/10 18:21:12 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"
#include "sh_error.h"
#include "editor.h"
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

static void	free_exit(int r, t_ast *head)
{
	free_shell();
	free_editor();
	del_ast(&head);
	exit(r);
}

static int	do_pipe(t_ast *el, int *pdes, t_ast *head)
{
	int		r;
	pid_t	child;
	static	int i = 0;

	i++;
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
		r = run_ast(el->left, head);
		free_exit(r, head);

	}
	dup2(pdes[READ_END], STDIN_FILENO);
	close(pdes[WRITE_END]);
	r = run_ast(el->right, head);
	return (r);
}

int	exec_pipe(t_ast *el, t_ast *head)
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
		r = do_pipe(el, pdes, head);
		free_exit(r, head);
	}
	else
		waitpid(child, &r, 0);
	return (r);
}
