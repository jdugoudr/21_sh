/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_shift_right.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 00:07:51 by mdaoud            #+#    #+#             */
/*   Updated: 2019/07/04 15:38:14 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "editor.h"

void			keypress_shift_right(void)
{
	if (g_editor->cur_pos == g_editor->cmd_sze)
		return ;
	while (g_editor->cmd[g_editor->cur_pos] != ' '
		&& g_editor->cmd[g_editor->cur_pos] != '\n')
	{
		move_cursor_right();
		if (g_editor->cur_pos == g_editor->cmd_sze)
			return ;
	}
	while (g_editor->cmd[g_editor->cur_pos] == ' '
		|| g_editor->cmd[g_editor->cur_pos] == '\n')
	{
		move_cursor_right();
		if (g_editor->cur_pos == g_editor->cmd_sze)
			return ;
	}
	if (g_editor->cmd[g_editor->cur_pos] == ' ')
		move_cursor_right();
}
