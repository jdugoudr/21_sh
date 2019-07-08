/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:19:34 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 18:04:45 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "sh_error.h"
#include "shell21.h"
#include "editor.h"
#include "ast.h"
#include "libft.h"

void	del_saved_fd(t_fd **fd_lst)
{
	t_fd	*next_el;
	t_fd	*el;

	el = *fd_lst;
	while (el)
	{
		next_el = el->next;
		free(el);
		el = next_el;
	}
	*fd_lst = NULL;
}

void	reset_term(t_ast *head, int ret)
{
	free_shell();
	free_editor();
	del_ast(&head);
	exit(ret);
}

int		is_saved(t_fd *fd_lst, int fd)
{
	int	i;

	i = 0;
	while (fd_lst)
	{
		if (fd_lst->old_fd == fd)
			return (1);
		fd_lst = fd_lst->next;
	}
	return (0);
}

t_fd	*add_value(t_fd *fd_lst, int to_save, int saved)
{
	t_fd	*new_el;

	if ((new_el = malloc(sizeof(t_fd))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		del_saved_fd(&fd_lst);
		return (NULL);
	}
	new_el->old_fd = to_save;
	new_el->save_fd = saved;
	new_el->next = fd_lst;
	return (new_el);
}

/*
** We creat a backup for the given fd
** If the dup creat a fd wich is already
** in the list. That's mean the user already
** closed this fd. So we re-do a dup until we
** find a "non-used" fd.
*/

int		save_fd(t_fd **fd_lst, int fd)
{
	int save;
	int r;

	if ((save = dup(fd)) == -1)
		return (-1);
	if (is_saved(*fd_lst, save))
	{
		r = save_fd(fd_lst, fd);
		close(save);
		return (r);
	}
	return (save);
}
