/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:09:59 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/28 15:50:06 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		shift_string_left(void)
{
	int		i;

	if (g_editor->cur_pos == 0)
		return ;
	i = g_editor->cur_pos - 1;
	i = (i < 0 ? 0 : i);
	while (i <= (int)g_editor->cmd_sze)
	{
		g_editor->cmd[i] = g_editor->cmd[i + 1];
		i++;
	}
}

void			remove_char(void)
{
	if (g_editor->cmd_sze != 0)
	{
		g_editor->cmd_sze--;
		shift_string_left();
		command_write();
		move_cursor_left();
	}
}
