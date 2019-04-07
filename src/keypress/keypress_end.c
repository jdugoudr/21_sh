/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:26:11 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/28 13:44:33 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static void		get_dim(void)
{
	int		x;

	x = g_editor->cmd_sze - g_editor->win_width + g_editor->offset;
	if (x < 0)
		x = 0;
	g_editor->max_line = x / g_editor->win_width;
	if (x % g_editor->win_width)
		g_editor->max_line++;
	g_editor->cur_pos = g_editor->cmd_sze;
	x = g_editor->cmd_sze + g_editor->offset;
	g_editor->line = x / g_editor->win_width;
	g_editor->col = x % g_editor->win_width;
}

void			keypress_end(void)
{
	size_t	i;
	int		x;

	keypress_home();
	get_dim();
	g_editor->cur_pos = g_editor->cmd_sze;
	x = g_editor->cmd_sze + g_editor->offset;
	g_editor->line = x / g_editor->win_width;
	g_editor->col = x % g_editor->win_width;
	i = 0;
	while (i < g_editor->max_line)
	{
		tputs(tgetstr("do", NULL), 1, tputs_char);
		i++;
	}
	tputs(tgetstr("cr", NULL), 1, tputs_char);
	i = 0;
	while (i < g_editor->col)
	{
		tputs(tgetstr("nd", NULL), 1, tputs_char);
		i++;
	}
}