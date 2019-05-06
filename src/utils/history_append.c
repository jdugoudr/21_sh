/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 17:51:35 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/29 16:37:37 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

/*
** Append a command to the history.
** Put the history pointer on the last entry.
*/

static int		to_add(t_shell *shell, char *name)
{
	t_history *ptr;

	if (ft_strequ(name, ""))
		return (0);
	if (shell->hist == NULL)
		return (1);
	ptr = shell->hist;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ft_strcmp(ptr->name, name));
}

void			history_append(t_shell *shell, char *name)
{
	t_history	*node;
	t_history	*tmp;

	if (!to_add(shell, name))
		return ;
	if ((node = malloc(sizeof(t_history))) == NULL)
		ft_exit("malloc", 1, EXIT_FAILURE);
	ft_strcpy(node->name, name);
	shell->hist_ptr = node;
	node->next = NULL;
	if (shell->hist == NULL)
	{
		node->prev = NULL;
		shell->hist = node;
		return ;
	}
	tmp = shell->hist;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
}
