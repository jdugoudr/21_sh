/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:20:33 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/02 10:28:34 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include <sys/ioctl.h>

static void		get_dim(void)
{
	int		x;

	x = g_editor->cmd_sze - g_editor->win_width + g_editor->offset;
	x = (x < 0 ? 0 : x);
	g_editor->max_line = x / g_editor->win_width;
	if (x % g_editor->win_width || (x % g_editor->win_height == 0\
		&& g_editor->cmd_sze + g_editor->offset > g_editor->win_width))
		g_editor->max_line++;
	x = g_editor->cur_pos + g_editor->offset;
	g_editor->line = x / g_editor->win_width;
	g_editor->col = x % g_editor->win_width;
}

void			rewrite_lines(void)
{
	size_t	i;

	get_dim();
	command_erase();
	move_cursor_home();
	display_prompt();
	ft_printf("%s", g_editor->cmd);
	move_cursor_home();
	i = 0;
	while (i < g_editor->line)
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