/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_less_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:10:25 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/02 18:46:19 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"
#include "sh_error.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
** Here we redirect el->right file descriptor int el->left input.
** We save the current input, dup the new input in the current input,
** execute the command, and then set again the input to the save one.
*/

static int	get_fd(char *name_file)
{
	int	fd;

	if (name_file[0] == '-')
	{
		ft_dprintf(STDERR_FILENO, BAD_FD, "stdin");
		return (-1);
	}
	else
	{
		fd = ft_atoi(name_file);
		if (write(fd, "", 0) == -1)
		{
			ft_dprintf(STDERR_FILENO, BAD_FD, fd);
			return (-1);
		}
	}
	return (fd);
}

static int	do_dup(t_ast *el, int fd_in, t_shell *shell, t_ast *head)
{
	int	r;
	int	save_fd;
	int	fd;

	r = 0;
	if ((fd = get_fd(el->right->value)) == -1)
		return (1);
	save_fd = dup(fd_in);
	if (save_fd == -1)
		r = -1;
	else if (dup2(fd, fd_in) == -1)
		r = -1;
	r = run_ast(el->left, shell, head);
	if (dup2(save_fd, fd_in) == -1)
		r = -1;
	if (r == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	close(fd);
	return (r);
}

int			exec_less_fd(t_ast *el, t_shell *shell, t_ast *head)
{
	int	fd_in;

	fd_in = STDIN_FILENO;
	if (el->right == NULL || el->right->value == NULL)
		return (1);
	if (el->value)
		fd_in = ft_atoi(el->value);
	return (do_dup(el, fd_in, shell, head));
}
