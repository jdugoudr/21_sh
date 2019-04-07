/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_rightarrow.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:53:27 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/28 13:44:33 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void		keypress_rightarrow(void)
{
	if (g_editor->cur_pos == g_editor->cmd_sze)
		return ;
	if (g_editor->col == g_editor->win_width - 1)
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

