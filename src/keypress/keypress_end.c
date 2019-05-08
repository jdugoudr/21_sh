/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:26:11 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/21 17:38:44 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

// void			keypress_end(void)
// {
// 	size_t	i;
// 	int		x;

// 	// get_dim();
// 	keypress_home();
// 	g_editor->cur_pos = g_editor->cmd_sze;
// 	x = g_editor->cmd_sze + g_editor->offset;
// 	g_editor->line = x / g_editor->win_width;
// 	g_editor->col = x % g_editor->win_width;
// 	i = 0;
// 	while (i < g_editor->max_line)
// 	{
// 		tputs(tgetstr("do", NULL), 1, tputs_char);
// 		i++;
// 	}
// 	tputs(tgetstr("cr", NULL), 1, tputs_char);
// 	i = 0;
// 	while (i < g_editor->col)
// 	{
// 		tputs(tgetstr("nd", NULL), 1, tputs_char);
// 		i++;
// 	}
// }

void			keypress_end(void)
{
	command_erase();
	g_editor->cur_pos = g_editor->cmd_sze;
	command_write();
}