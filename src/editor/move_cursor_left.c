/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:54:59 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/09 15:10:54 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static size_t	get_col_count(void)
{
	int		tmp;
	size_t	count;

	if (g_editor->cur_pos && g_editor->cmd[g_editor->cur_pos - 1] == '\n')
	{
		count = 0;
		tmp = g_editor->cur_pos - 2;
		while (tmp >= 0 && g_editor->cmd[tmp] != '\n')
		{
			tmp--;
			count++;
		}
		tmp = (g_editor->line == 0 ? g_editor->offset : 0);
		g_editor->col = 0;
		return (count + tmp);
	}
	return (g_editor->win_width - 1);
}

void			move_cursor_left(void)
{
	size_t	count;

	if (g_editor->col <= g_editor->offset && g_editor->line == 0)
		return ;
	if (g_editor->col == 0 && g_editor->line != 0)
	{
		g_editor->line--;
		count = get_col_count();
		tputs(tgetstr("up", NULL), 1, tputs_char);
		while (g_editor->col < count)
		{
			tputs(tgetstr("nd", NULL), 1, tputs_char);
			g_editor->col++;
		}
	}
	else
	{
		tputs(tgetstr("le", NULL), 1, tputs_char);
		g_editor->col--;
	}
	g_editor->cur_pos--;
}
