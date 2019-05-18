/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:44:45 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/18 16:09:34 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"
#include "sh_error.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
** Here we execute <, <<, >, >> redirection.
** The open mode are given in params. 
** >	(O_WRONLY | O_CREAT | O_TRUNC)
** >>	(O_WRONLY | O_CREAT | O_APPEND)
** <	(O_RDONLY)
** <<	(O_RDONLY)
** fd_in = STDOUT_FILENO : >, >>
**		 = STDIN_FILENO  : <, <<
**
** In the case of << redirection. We first creat a tempory file /tmp/heredoc_21
** We write there all of what was written by users, close then re-open the
** tempory file for reading.
**
** Before to apply a redirection we have to save the current fd to
** back to normal after execution.
** All fd are saved in int array. We check before to save it if the fd is
** not already in this table.
*/

static int	write_heredoc(int open_flag, char *str)
{
	int	len;
	int fd;

	if ((fd = open(HERE_DOC, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (-1);
	}
	len = ft_strlen(str);
	if (write(fd, str, len) == -1)
	{
		close(fd);
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (-1);
	}
	close(fd);
	get_fd(HERE_DOC, open_flag, &fd);
	return (fd);
}

static int 	left(int type, int fd_from, t_save_fd **fd_lst)
{
	if (type & (LESS_TOK | DLESS_TOK))
	{
		if (check_left_fd(fd_lst, fd_from, type) || *fd_lst == NULL)
			return (1);
	}
	else
	{
		if (check_left_fd(fd_lst, fd_from, type) || *fd_lst == NULL)
			return (1);
	}
	return (0);
}

static int	do_dup(t_ast *el, int fd_from, int fd_to, t_save_fd **fd_lst)
{
	if (fd_from != fd_to && check_right_fd(*fd_lst, fd_to, el->type))
	{
		ft_dprintf(STDERR_FILENO, BAD_FD, el->right->value);
		return (1);
	}
	if (left(el->type, fd_from, fd_lst))
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	if (fd_from == fd_to)
		close(fd_from);
	else if (read(fd_to, NULL, 0) == -1)
		close(fd_from);
	else if (dup2(fd_to, fd_from) == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (0);
}

int	exec_in_redir(t_ast *el, t_save_fd **save_fd, int open_flag, int fd_in)
{
	int	work_fd;

	if (el->right == NULL || el->right->value == NULL)
		return (1);
	if (el->value)
		fd_in = ft_atoi(el->value);
	if (el->type & DLESS_TOK)
	{
		if ((work_fd = write_heredoc(open_flag, el->right->value)) == -1)
			return (1);
	}
	else if (el->type & (LESS_TOK | DLESS_TOK))
	{
		if (get_fd(el->right->value, open_flag, &work_fd))
			return (1);
	}
	else
	{
		if ((el->right->value)[0] == '-')
			work_fd = fd_in;
		else if (file_descriptor(el->right->value, &work_fd))
			return (1);
	}
	return (do_dup(el, fd_in, work_fd, save_fd));
}
