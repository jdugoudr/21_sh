/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_great.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:02:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/06 17:20:39 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "run_ast.h"
#include "sh_error.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
** Here we redirect el->left output in el->right file, trunc mode.
** The fork child execute redirection and run el->left then
** EXIT and not return to kill himself.
** The fork parent wait and return the value of his child
*/

int	exec_great(t_ast *el)
{
	pid_t	child;
	int		fd;
	int		r;

	r = 0;
	fd = -1;
	if (el->right->value)
		fd = open(el->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || el->right->value == NULL)
		return (1);
	child = fork();
	if (child == 0)
	{
		dup2(fd, STDOUT_FILENO);
		r = run_ast(el->left);
		close(fd);
		exit(r);
	}
	else if (child == -1)
	{
		ft_fprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	else
	{
		close(fd);
		waitpid(child, &r, 0);
		return (r);
	}
}
