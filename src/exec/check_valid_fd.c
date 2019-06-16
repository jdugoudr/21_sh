/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:39:08 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 18:02:21 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "sh_error.h"
#include "token_define.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	is_number(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

/*
** Check if the fd given is truly a fd
*/

int			file_descriptor(char *value, int *new_fd)
{
	int	fd;

	if (is_number(value) == 0)
	{
		ft_dprintf(STDERR_FILENO, BAD_FD, value);
		return (1);
	}
	else if ((fd = ft_atoi(value)) < 0)
	{
		ft_dprintf(STDERR_FILENO, BAD_FD, value);
		return (1);
	}
	if (fd >= OPEN_MAX)
	{
		ft_dprintf(STDERR_FILENO, BAD_FD, value);
		return (1);
	}
	*new_fd = fd;
	return (0);
}

/*
** We open a file and add the value in the list with backup -1 to close
** it at the and of redirection
*/

int			get_fd(char *nm_fl, int open_flag, int *new_fd, t_fd **fd_lst)
{
	int	fd;

	if (open_flag & O_CREAT)
		fd = open(nm_fl, open_flag, 0644);
	else
		fd = open(nm_fl, open_flag);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, CANT_OPEN, nm_fl);
		return (1);
	}
	if ((*fd_lst = add_value(*fd_lst, fd, -1)) == NULL)
		return (1);
	*new_fd = fd;
	return (0);
}

/*
** We check the fd where we will do to/from the redirection.
** The fd need to be a open fd.
** If the fd is a backup, it's not a right redirection.
** If the fd is open but was close at the begining (4>&2 will open fd 4),
** it's not right.
** If we can't read/write from/on it. It's not a right redirection.
**
** If we the fd is saved and backup is not -1. That's mean the fd is right.
** If the fd is not saved and we can read/write from/on it. It's a right fd.
*/

int			check_right_fd(t_fd *fd_lst, int fd, int tok_red)
{
	while (fd_lst)
	{
		if (fd_lst->save_fd == fd)
			return (1);
		if (fd_lst->old_fd == fd && fd_lst->save_fd == -1)
			return (1);
		if (fd_lst->old_fd == fd && fd_lst->save_fd != -1)
			return (0);
		fd_lst = fd_lst->next;
	}
	if (tok_red & OUT_REDIR)
	{
		if (write(fd, "", 0) < 0)
			return (1);
	}
	else if (read(fd, NULL, 0) < 0)
		return (1);
	return (0);
}

/*
** We check given fd we want to redirect.
** If this fd already use as a fd backup => we replace the backup
** If we can't write or read on it, that's mean the fd is close.
** We save it with value -1 to know we will need to close it at
** the end of redirect.
** We add the fd and his backup in the fd list.
*/

int			check_left_fd(t_fd **fd_lst, int fd, int tok_red)
{
	t_fd	*el;
	int		save;

	save = -1;
	el = *fd_lst;
	while (el)
	{
		if (el->save_fd == fd)
		{
			if ((el->save_fd = save_fd(fd_lst, fd)) == -1)
				return (1);
			close(fd);
			break ;
		}
		el = el->next;
	}
	if (tok_red & OUT_REDIR)
	{
		if (write(fd, "", 0) == 0 && (save = save_fd(fd_lst, fd)) == -1)
			return (1);
	}
	else if (read(fd, NULL, 0) == 0 && (save = save_fd(fd_lst, fd)) == -1)
		return (1);
	*fd_lst = add_value(*fd_lst, fd, save);
	return (0);
}
