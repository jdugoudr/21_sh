/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:19:34 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/18 16:10:32 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "sh_error.h"
#include "libft.h"

void print_fd(t_save_fd *el)
{
	char	*s;
	while (el)
	{
		write(1, "in ", 3);
		s = ft_itoa(el->old_fd);
		write(1, s, ft_strlen(s));
		write(1, " save in ", 9);
		s = ft_itoa(el->save_fd);
		write(1, s, ft_strlen(s));
//		s = ft_itoa(el->file_open);
//		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
		el = el->next;
	}
}

void		del_saved_fd(t_save_fd **fd_lst)
{
	t_save_fd	*next_el;
	t_save_fd	*el;

	el = *fd_lst;
	while (el)
	{
		next_el = el->next;
		free(el);
		el = next_el;
	}
	*fd_lst = NULL;
}

int 		is_saved(t_save_fd *fd_lst, int fd)
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

t_save_fd	*add_value(t_save_fd *fd_lst, int to_save, int saved)
{
	t_save_fd	*new_el;

	if ((new_el = malloc(sizeof(t_save_fd))) == NULL)
	{
		del_saved_fd(&fd_lst);
		return (NULL);
	}
	new_el->old_fd = to_save;
	new_el->save_fd = saved;
	new_el->next = fd_lst;
//	new_el->file_open = -1;
	return (new_el);
}

int 		save_fd(t_save_fd **fd_lst, int fd)
{
	int save;
	int r;

	if ((save = dup(fd)) == -1)
		return (-1);
	if (is_saved(*fd_lst, save))//si save existe deja dans la table (donc un fd ferme)
	{
		r = save_fd(fd_lst, fd);
		close(save);
		return (r);
	}
	return (save);
}
