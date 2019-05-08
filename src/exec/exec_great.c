/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_great.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:02:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/08 20:27:20 by jdugoudr         ###   ########.fr       */
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

static int	get_fd(char *name_file)
{
	int	fd;

	fd = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, CANT_OPEN, name_file);
		return (-1);
	}
	return (fd);
}

static int	do_dup(t_ast *el, int fd_in, t_ast *head)
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
	r = run_ast(el->left, head);
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

int	exec_great(t_ast *el, t_ast *head)
{
	int		fd_in;

	fd_in = STDOUT_FILENO;
	if (el->right == NULL || el->right->value == NULL)
		return (1);
	if (el->value)
		fd_in = ft_atoi(el->value);
	return (do_dup(el, fd_in, head));
}
