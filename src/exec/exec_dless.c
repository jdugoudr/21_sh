/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dless.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:01:58 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/06 16:22:13 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "ast.h"
#include "sh_error.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
** Here we execute a heredocument
** We write the value of next->value in a tampory file to use it as
** simple less redirect.
** We save the current input, dup the new input in the current input,
** execute the command, and then set again the input to the save one.
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

static int	do_dup(t_ast *el, int fd_in, t_shell *shell, t_ast *head)
{
	int	r;
	int	save_fd;
	int	fd;

	r = 0;
	if ((fd = open(HERE_DOC, O_RDONLY)) == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	if ((save_fd = dup(fd_in)) == -1)
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


int	exec_dless(t_ast *el, t_shell *shell, t_ast *head)
{
	int	fd;
	int	fd_in;

	fd_in = STDIN_FILENO;
	if ((fd = open(HERE_DOC, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	if (write_heredoc(fd, el->right->value))
		return (1);
	close(fd);
	return (do_dup(el, fd_in, shell, head));
}
