/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_uparrow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:33:49 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/29 17:45:26 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static void		load_history_entry(t_shell *shell)
{
	ft_strcpy(g_editor->cmd, shell->hist_ptr->name);
	g_editor->cmd_sze = ft_strlen(shell->hist_ptr->name);
	g_editor->cur_pos = ft_strlen(shell->hist_ptr->name);
	rewrite_lines();
}

void			keypress_uparrow(t_shell *shell)
{
	if (shell->hist == NULL)
		return ;
	if (shell->hist_ptr == NULL)
	{
		shell->hist_ptr = shell->hist;
		while (shell->hist_ptr->next != NULL)
			shell->hist_ptr = shell->hist_ptr->next;
		load_history_entry(shell);
	}
	else if (shell->hist_ptr->prev != NULL)
	{
		shell->hist_ptr = shell->hist_ptr->prev;
		load_history_entry(shell);
	}
}
