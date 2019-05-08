/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_home.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:22:09 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/24 17:12:31 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			keypress_home(void)
{
	// size_t	i;

	// i = g_editor->line;
	// while (i > 0)
	// {
	// 	tputs(tgetstr("up", NULL), 1, tputs_char);
	// 	i--;
	// }
	// tputs(tgetstr("cr", NULL), 1, tputs_char);
	// i = 0;
	// while (i < g_editor->offset)
	// {
	// 	tputs(tgetstr("nd", NULL), 1, tputs_char);
	// 	i++;
	// }
	// g_editor->line = 0;
	// g_editor->col = g_editor->offset;
	// g_editor->cur_pos = 0;
	command_erase();
	g_editor->cur_pos = 0;
	command_write();
}

// void			keypress_home(void)
// {
// 	size_t	i;
// 	int		col0;

// 	i = 0;
// 	col0 = g_editor->col == g_editor->win_width;
// 	while (i < g_editor->max_line - col0)
// 	{
// 		tputs(tgetstr("up", NULL), 1, tputs_char);
// 		i++;
// 	}
// 	tputs(tgetstr("cr", NULL), 1, tputs_char);
// 	i = 0;
// 	while (i < g_editor->offset)
// 	{
// 		tputs(tgetstr("nd", NULL), 1, tputs_char);
// 		i++;
// 	}
// 	g_editor->line = 0;
// 	g_editor->col = g_editor->offset;
// 	g_editor->cur_pos = 0;
// }