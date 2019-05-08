/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 17:51:35 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/08 19:18:48 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "sh_error.h"

/*
** Append a command to the history.
** Put the history pointer on the last entry.
*/

static int		to_add(char *name)
{
	t_history *ptr;

	if (ft_strequ(name, ""))
		return (0);
	if (g_shell->hist == NULL)
		return (1);
	ptr = g_shell->hist;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ft_strcmp(ptr->name, name));
}

void			history_append(char *name)
{
	t_history	*node;
	t_history	*tmp;

	if (!to_add(name))
		return ;
	if ((node = malloc(sizeof(t_history))) == NULL)
		ft_exit(INTERN_ERR, 1, 1, EXIT_FAILURE);
	ft_strcpy(node->name, name);
	g_shell->hist_ptr = node;
	node->next = NULL;
	if (g_shell->hist == NULL)
	{
		node->prev = NULL;
		g_shell->hist = node;
		return ;
	}
	tmp = g_shell->hist;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
}
