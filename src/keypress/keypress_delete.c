/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:06:45 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 18:23:07 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "editor.h"

static void		shift_string_left(void)
{
	int		i;

	i = g_editor->cur_pos;
	i = (i < 0 ? 0 : i);
	while (i < (int)g_editor->cmd_sze)
	{
		g_editor->cmd[i] = g_editor->cmd[i + 1];
		i++;
	}
}

void			keypress_delete(void)
{
	if (g_editor->cmd_sze != 0 && g_editor->cur_pos != g_editor->cmd_sze)
	{
		command_erase();
		shift_string_left();
		g_editor->cmd_sze--;
		command_write();
	}
}
