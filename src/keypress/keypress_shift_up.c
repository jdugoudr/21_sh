/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_shift_up.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 23:49:36 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/28 13:44:33 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			keypress_shift_up(void)
{
	if (g_editor->line == 0 ||\
	(g_editor->line == 1 && g_editor->col <= g_editor->offset))
	{
		keypress_home();
		return ;
	}
	g_editor->cur_pos -= g_editor->win_width;
	g_editor->line--;
	tputs(tgetstr("up", NULL), STDOUT_FILENO, tputs_char);
}