/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_in_visual.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:36:49 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/03 14:52:46 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static void			write_cmd_in_visual(size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while (i < start)
	{
		dprintf(STDOUT_FILENO, "%c", g_editor->cmd[i]);
		i++;
	}
	tputs(tgetstr("mr", NULL), g_editor->tty_fd, tputs_char);
	while (i < end && g_editor->cmd[i])
	{
		dprintf(STDOUT_FILENO, "%c", g_editor->cmd[i]);
		i++;
	}
	tputs(tgetstr("me", NULL), g_editor->tty_fd, tputs_char);
	while (g_editor->cmd[i])
	{
		dprintf(STDOUT_FILENO, "%c", g_editor->cmd[i]);
		i++;
	}
}

void			write_in_visual(size_t start, size_t end)
{
	size_t	i;

	get_editor_dim();
	display_prompt();
	write_cmd_in_visual(start, end);
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