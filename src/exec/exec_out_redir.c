/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_out_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:32:52 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/20 12:18:14 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"
#include "sh_error.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
** Here we execute >, >>, >&, >>& redirection.
** The open mode are given in params. 
** >&	(O_WRONLY | O_CREAT | O_TRUNC)
** >>&	(O_WRONLY | O_CREAT | O_APPEND)
** >	(O_WRONLY | O_CREAT | O_TRUNC)
** >>	(O_WRONLY | O_CREAT | O_APPEND)
**
** fd_in = STDOUT_FILENO
** and is change if token have a non null value.
**
** Before to apply a redirection we have to save the current fd to
** back to normal after execution.
** fd opened file need to be save with a backup value -1.
** If we ask to redirect a closen fd (4 > f) we need to save 4 with a -1 backup.
**
** All fd are saved in int array. We check before to save it if the fd is
** not already in this table.
*/

static int 	left(int type, int fd_from, t_save_fd **fd_lst)
{
	if (check_left_fd(fd_lst, fd_from, type) || *fd_lst == NULL)
		return (1);
	return (0);
}

static int	do_dup(t_ast *el, int fd_from, int fd_to, t_save_fd **fd_lst)
{
	if (fd_from != fd_to && el->type & FD_REDIR && check_right_fd(*fd_lst, fd_to, el->type))
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
	else if (write(fd_to, "", 0) == -1)
		close(fd_from);
	else if (dup2(fd_to, fd_from) == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (0);
}

int			exec_out_redir(t_ast *el, t_save_fd **fd_lst, int open_flag, int fd_in)
{
	int work_fd;

	if (el->right == NULL || el->right->value == NULL)
		return (1);
	if (el->value)
		if ((fd_in = ft_atoi(el->value)) == -1)
			return (1);
	if (el->type & (GREAT_TOK | DGREAT_TOK))
	{
		if (get_fd(el->right->value, open_flag, &work_fd, fd_lst))
			return (1);
	}
	else
	{
		if ((el->right->value)[0] == '-')
			work_fd = fd_in;
		else if (file_descriptor(el->right->value, &work_fd))
			return (1);
	}
	return (do_dup(el, fd_in, work_fd, fd_lst));
}