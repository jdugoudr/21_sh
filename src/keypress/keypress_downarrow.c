/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_downarrow.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:36:58 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/30 17:50:15 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"


void			keypress_downarrow(t_shell *shell)
{
	if (shell->hist == NULL || shell->hist_ptr == NULL)
		return ;
	if (shell->hist_ptr->next != NULL)
	{
		shell->hist_ptr = shell->hist_ptr->next;
		ft_strcpy(g_editor->cmd, shell->hist_ptr->name);
		g_editor->cmd_sze = ft_strlen(shell->hist_ptr->name);
		g_editor->cur_pos = ft_strlen(shell->hist_ptr->name);
		rewrite_lines();
	}
	else
	{
		command_reset();
		rewrite_lines();
		shell->hist_ptr = NULL;
	}
}