/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_great.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:02:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/07 14:39:14 by jdugoudr         ###   ########.fr       */
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

static int	do_fork(t_ast *el, int fd, int fd_in)
{
	pid_t	child;
	int		r;

	child = fork();
	if (child == -1)
	{
		ft_fprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	else if (child == 0)
	{
		dup2(fd, fd_in);
		r = run_ast(el->left);
		close(fd);
		exit(r);
	}
	else
	{
		waitpid(child, &r, 0);
		return (r);
	}
	return (0);
}

static int	regular_file(t_ast *el, char *name_file, int fd_in)
{
	int	fd;
	int	ret;

	fd = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, CANT_OPEN, name_file);
		return (1);
	}
	ret = do_fork(el, fd, fd_in);
	close(fd);
	return (ret);
}

static int	file_descriptor(t_ast *el, int fd_in)
{
	int	fd;

	if ((el->right->value)[1] == '-')
		return (regular_file(el, CLOSE_OUTPUT, fd_in));
	else
	{
		fd = ft_atoi((el->right->value) + 1);
		if (write(fd, "", 0) == -1)
		{
			ft_fprintf(STDERR_FILENO, BAD_FD, fd);
			return (1);
		}
	}
	return (do_fork(el, fd, fd_in));
}

int	exec_great(t_ast *el)
{
	int		fd_in;

	fd_in = STDOUT_FILENO;
	if (el->right == NULL || el->right->value == NULL)
		return (1);
	if (el->value)
		fd_in = ft_atoi(el->value);
	if (el->right->value[0] != '&')
		return (regular_file(el, el->right->value, fd_in));
	else
		return (file_descriptor(el, fd_in));
}
