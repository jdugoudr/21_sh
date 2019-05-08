/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_backspace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:06:45 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/23 17:45:00 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

// void			keypress_backspace(void)
// {
// 	if (g_editor->cmd_sze != 0 && g_editor->cur_pos != 0)
// 	{
// 		shift_string_left();
// 		if (g_editor->cur_pos == g_editor->cmd_sze)
// 		{
// 			move_cursor_left();
// 			// move_cursor_left();
// 			tputs(tgetstr("dc", NULL), 1, tputs_char);
// 			g_editor->cmd_sze--;
// 		}
// 		else
// 		{
// 			if (g_editor->col == 0 && g_editor->line != 0 && g_editor->cur_pos == g_editor->cmd_sze - 1)
// 				tputs(tgetstr("up", NULL), 1, tputs_char);
// 			g_editor->cmd_sze--;
// 			command_write();
// 			move_cursor_left();
// 			// move_cursor_left();
// 		}
// 	}
// }

static void		shift_string_left(void)
{
	int		i;

	i = g_editor->cur_pos - 1;
	i = (i < 0 ? 0 : i);
	while (i < (int)g_editor->cmd_sze)
	{
		g_editor->cmd[i] = g_editor->cmd[i + 1];
		i++;
	}
}

void			keypress_backspace(void)
{
	if (g_editor->cmd_sze != 0 && g_editor->cur_pos != 0)
	{
		command_erase();
		shift_string_left();
		g_editor->cur_pos--;
		g_editor->cmd_sze--;
		command_write();
	}
}