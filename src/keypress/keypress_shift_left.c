/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_shift_left.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 00:07:51 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/23 15:51:24 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

// void			keypress_shift_left(void)
// {
// 	if (g_editor->cur_pos != 0)
// 		move_cursor_left();
// 	while (g_editor->cmd[g_editor->cur_pos] == ' ')
// 	{
// 		move_cursor_left();
// 		if (g_editor->cur_pos == 0)
// 			return ;
// 	}
// 	while (g_editor->cmd[g_editor->cur_pos] != ' ')
// 	{
// 		move_cursor_left();
// 		if (g_editor->cur_pos == 0)
// 			return ;
// 	}
// 	if (g_editor->cmd[g_editor->cur_pos] == ' ')
// 		move_cursor_right();
// }

void			keypress_shift_left(void)
{
	if (g_editor->cur_pos != 0)
		move_cursor_left();
	while (g_editor->cmd[g_editor->cur_pos] == ' ' ||
		g_editor->cmd[g_editor->cur_pos] == '\n')
	{
		move_cursor_left();
		if (g_editor->cur_pos == 0)
			return ;
	}
	while (g_editor->cmd[g_editor->cur_pos] != ' ' &&
		g_editor->cmd[g_editor->cur_pos] != '\n')
	{
		move_cursor_left();
		if (g_editor->cur_pos == 0)
			return ;
	}
	if (g_editor->cmd[g_editor->cur_pos] == ' ' ||
		g_editor->cmd[g_editor->cur_pos] == '\n')
		move_cursor_right();
}