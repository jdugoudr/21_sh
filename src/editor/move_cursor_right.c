/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:53:27 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/10 18:55:02 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		move_cursor_right(void)
{
	if (g_editor->cur_pos == g_editor->cmd_sze)
		return ;
	if (g_editor->col == g_editor->win_width - 1
		|| g_editor->cmd[g_editor->cur_pos] == '\n')
	{
		tputs(tgetstr("do", NULL), 1, tputs_char);
		g_editor->col = 0;
		g_editor->line++;
		g_editor->max_line++;
	}
	else
	{
		tputs(tgetstr("nd", NULL), 1, tputs_char);
		g_editor->col++;
	}
	g_editor->cur_pos++;
}
