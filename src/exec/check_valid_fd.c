/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:39:08 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/20 10:42:23 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "sh_error.h"
#include "token_define.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int 	is_number(char *str)
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

int	file_descriptor(char *value, int *new_fd)
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

int	get_fd(char *name_file, int open_flag, int *new_fd, t_save_fd **fd_lst)
{
	int	fd;

	if (open_flag & O_CREAT)
		fd = open(name_file, open_flag, 0644);
	else
		fd = open(name_file, open_flag);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, CANT_OPEN, name_file);
		return (1);
	}
	if ((*fd_lst = add_value(*fd_lst, fd, -1)) == NULL)
		return (1);
	*new_fd = fd;
	return (0);
}

int 		check_right_fd(t_save_fd *fd_lst, int fd, int tok_red)
{
	while (fd_lst)
	{
		if (fd_lst->save_fd == fd)//si le fd est une sauvegarde
			return (1);
		if (fd_lst->old_fd == fd && fd_lst->save_fd == -1)//si le fd etait un fd ferme
			return (1);
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

int 		check_left_fd(t_save_fd **fd_lst, int fd, int tok_red)
{
	t_save_fd	*el;
	int 		save;

	save = -1;
	el = *fd_lst;
	while (el)
	{
		if (el->save_fd == fd)//si le fd est une sauvegarde
		{
			if ((el->save_fd = save_fd(fd_lst, fd)) == -1)//on remplace le fd
				return (1);
			close(fd);//on ferme l'ancienne sauvegarde
			break ;
		}
		el = el->next;
	}
	if (tok_red & OUT_REDIR)//
	{
		if (write(fd, "", 0) == 0 && (save = save_fd(fd_lst, fd)) == -1)
			return (1);
	}
	else if ((save = save_fd(fd_lst, fd)) == -1)
		return (1);
	*fd_lst = add_value(*fd_lst, fd, save);
	return (0);
}