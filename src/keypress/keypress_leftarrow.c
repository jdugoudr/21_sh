/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_leftarrow.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:54:59 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/28 18:33:58 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void		keypress_leftarrow(void)
{
	if (g_editor->col <= g_editor->offset && g_editor->line == 0)
		return ;
	if (g_editor->col == 0 && g_editor->line != 0)
	{
		g_editor->line--;
		tputs(tgetstr("up", NULL), 1, tputs_char);
		while (g_editor->col < g_editor->win_width - 1)
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
