/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_shift_left.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 00:07:51 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/10 18:48:35 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "editor.h"

void			keypress_shift_left(void)
{
	if (g_editor->cur_pos != 0)
		move_cursor_left();
	while (g_editor->cmd[g_editor->cur_pos] == ' '
		|| g_editor->cmd[g_editor->cur_pos] == '\n')
	{
		move_cursor_left();
		if (g_editor->cur_pos == 0)
			return ;
	}
	while (g_editor->cmd[g_editor->cur_pos] != ' '
		&& g_editor->cmd[g_editor->cur_pos] != '\n')
	{
		move_cursor_left();
		if (g_editor->cur_pos == 0)
			return ;
	}
	if (g_editor->cmd[g_editor->cur_pos] == ' '
		|| g_editor->cmd[g_editor->cur_pos] == '\n')
		move_cursor_right();
}
