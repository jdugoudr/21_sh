/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:44:45 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 17:57:06 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"
#include "sh_error.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
** Here we execute <, <<, <& redirection.
** The open mode are given in params.
** <&	(O_RDONLY)
** <	(O_RDONLY)
** <<	(O_RDONLY)
**
** fd_in = STDIN_FILENO
** and is change if token have a non null value.
**
** Before to apply a redirection we have to save the current fd to
** back to normal after execution.
** fd opened file need to be save with a backup value -1.
** If we ask to redirect a closen fd (4 < f) we need to save 4 with a -1 backup.
**
** All fd are saved in int array. We check before to save it if the fd is
** not already in this table.
*/

static int	write_heredoc(int open_flag, char *str, t_fd **fd_lst)
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
	if (get_fd(HERE_DOC, open_flag, &fd, fd_lst))
		return (-1);
	return (fd);
}

static int	left(int type, int fd_from, t_fd **fd_lst)
{
	if (check_left_fd(fd_lst, fd_from, type) || *fd_lst == NULL)
		return (1);
	return (0);
}

static int	do_dup(t_ast *el, int fd_from, int fd_to, t_fd **fd_lst)
{
	if (fd_from != fd_to && el->type & FD_REDIR
		&& check_right_fd(*fd_lst, fd_to, el->type))
	{
		ft_dprintf(STDERR_FILENO, BAD_FD, el->prev->value);
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

static int	less_fd(char *str, int *work_fd, int fd_in)
{
	if (str[0] == '-')
		*work_fd = fd_in;
	else
	{
		if (file_descriptor(str, work_fd))
			return (-1);
		if (*work_fd == fd_in)
			return (1);
	}
	return (0);
}

int			exec_in_redir(t_ast *el, t_fd **fd_lst, int o_flag, int fd_in)
{
	int	work_fd;
	int	r;

	if (el->prev == NULL || el->prev->value == NULL)
		return (1);
	if (el->value)
		fd_in = ft_atoi(el->value);
	if (el->type & DLESS_TOK)
	{
		if ((work_fd = write_heredoc(o_flag, el->prev->value, fd_lst)) == -1)
			return (1);
	}
	else if (el->type & (LESS_TOK | DLESS_TOK))
	{
		if (get_fd(el->prev->value, o_flag, &work_fd, fd_lst))
			return (1);
	}
	else if ((r = less_fd(el->prev->value, &work_fd, fd_in)))
	{
		if (r > 0)
			return (0);
		return (1);
	}
	return (do_dup(el, fd_in, work_fd, fd_lst));
}
