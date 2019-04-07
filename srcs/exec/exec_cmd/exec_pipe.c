/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 10:59:40 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/06 19:46:57 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "run_ast.h"
#include "sh_error.h"

/*
** Here we redirect el->left output in el->right input.
** The fork child execute redirection and run el->left then
** EXIT and not return to kill himself.
** The fork parent wait and run and return el->right.
** We have to fork two times, because if not, the redirection
** of the input in father process will still be effective when we return.
*/

static int	do_pipe(t_ast *el, int *pdes/*, pid_t child*/)
{
	int		r;
	pid_t	child;

	r = 0;
	child = fork();
	if (child == -1)
	{
		ft_fprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	if (child == 0)
	{
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		close(pdes[READ_END]);
		r = run_ast(el->left);
		exit(r);
	}
	else
	{
		dup2(pdes[READ_END], STDIN_FILENO);
		close(pdes[WRITE_END]);
		waitpid(child, &r, 0);
		r = run_ast(el->right);
		return (r);
	}
}

int	exec_pipe(t_ast *el)
{
	int		pdes[2];
	pid_t	child;
	int		r;

	r = 0;
	child = fork();
	if (child == -1)
	{
		ft_fprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	else if (child == 0)
	{
		if (pipe(pdes) == -1)
		{
			ft_fprintf(STDERR_FILENO, INTERN_ERR);
			return (1);
		}
		r = do_pipe(el, pdes);
		exit(r);
	}
	else
		waitpid(child, &r, 0);
	return (r);
}
