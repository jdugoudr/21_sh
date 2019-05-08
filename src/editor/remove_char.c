/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:06:45 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/28 13:44:33 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static void		shift_string_left(void)
{
	int		i;

	if (g_editor->cur_pos == 0)
		return ;
	i = g_editor->cur_pos - 1;
	i = (i < 0 ? 0 : i);
	while (i < (int)g_editor->cmd_sze)
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