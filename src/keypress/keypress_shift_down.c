/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_shift_down.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 23:49:36 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/28 13:44:33 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			keypress_shift_down(void)
{
	size_t	i;

	if (g_editor->cur_pos + g_editor->win_width > g_editor->cmd_sze)
	{
		keypress_end();
		return ;
	}
	g_editor->cur_pos += g_editor->win_width;
	g_editor->line++;
	tputs(tgetstr("do", NULL), STDOUT_FILENO, tputs_char);
	tputs(tgetstr("cr", NULL), 1, tputs_char);
	i = 0;
	while (i < g_editor->col)
	{
		tputs(tgetstr("nd", NULL), 1, tputs_char);
		i++;
	}
}