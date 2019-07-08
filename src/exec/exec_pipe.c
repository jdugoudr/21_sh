/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 10:59:40 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/17 14:26:07 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"
#include "sh_error.h"
#include "editor.h"
#include "libft.h"
#include <sys/types.h>
#include <signal.h>

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
	if (r)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

static int	dup_pipe(int *pdes)
{
	if (pipe(pdes) == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (0);
}

static int	do_pipe(t_ast *el, int *pdes, t_ast *head, int ret)
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
		dup2(pdes[READ_END], STDIN_FILENO);
		close(pdes[WRITE_END]);
		r = run_ast(el->right, head, ret);
		close(pdes[READ_END]);
		free_exit(r, head);
	}
	dup2(pdes[WRITE_END], STDOUT_FILENO);
	close(pdes[READ_END]);
	run_ast(el->left, head, ret);
	close(pdes[WRITE_END]);
	close(STDOUT_FILENO);
	waitpid(child, &r, 0);
	return (r);
}

static int	first_fork(t_ast *el, t_ast *head, int ret, int pdes[2])
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
	else if (child == 0)
	{
		if (dup_pipe(pdes) == 1)
			return (1);
		r = do_pipe(el, pdes, head, ret);
		free_exit(r, head);
	}
	else
		waitpid(child, &r, 0);
	return (r);
}

int			exec_pipe(t_ast *el, t_ast *head, int ret)
{
	int		pdes[2];
	int		r;

	if (el->father == NULL || el->father->type != PIPE_TOK)
		r = first_fork(el, head, ret, pdes);
	else
	{
		if (dup_pipe(pdes) == 1)
			return (1);
		r = do_pipe(el, pdes, head, ret);
	}
	return (r);
}
