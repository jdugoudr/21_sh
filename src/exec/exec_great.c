/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_great.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:02:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/14 16:13:48 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"
#include "sh_error.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
** Here we redirect el->left output in el->right file, trunc mode.
** We save the current output, dup the new output in the current output,
** execute the command, and then set again the output to the save one.
*/

static int	write_heredoc(int fd, char *str)
{
	int	len;

	len = ft_strlen(str);
	if (write(fd, str, len) == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (0);
}

static int	get_fd(char *name_file, int open_flag)
{
	int	fd;

	if (open_flag & O_CREAT)
		fd = open(name_file, open_flag, 0644);
	else
		fd = open(name_file, open_flag);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, CANT_OPEN, name_file);
		return (-1);
	}
	return (fd);
}

static int	do_dup(t_ast *el, int fd_in, int ***save_fd, int open_flag)
{
	int	fd;
	int	save;

	if (el->type & DLESS_TOK)
	{
		if ((fd = open(HERE_DOC, open_flag)) == -1)
		{
			ft_dprintf(STDERR_FILENO, INTERN_ERR);
			return (1);
		}
	}
	else if ((fd = get_fd(el->right->value, open_flag)) == -1)
		return (-1);
	if (is_saved(*save_fd, fd_in, 0) == 0)
	{
		if ((save = dup(fd_in)) == -1)
			return (-1);
		if ((*save_fd = add_value(*save_fd, fd_in, save)) == NULL)
			return (-1);
	}
	if (dup2(fd, fd_in) == -1)
		return (-1);
	return (fd);
}

int	exec_great(t_ast *el, int ***save_fd, int open_flag, int fd_in)
{
	int	fd;

	if (el->right == NULL || el->right->value == NULL)
		return (1);
	if (el->type & DLESS_TOK)
	{
		if ((fd = open(HERE_DOC, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		{
			ft_dprintf(STDERR_FILENO, INTERN_ERR);
			return (1);
		}
		if (write_heredoc(fd, el->right->value))
			return (1);
		close(fd);
	}
	if (el->value)
		fd_in = ft_atoi(el->value);
	fd = do_dup(el, fd_in, save_fd, open_flag);
	return (fd);
}
