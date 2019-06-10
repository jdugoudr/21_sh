/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 16:38:49 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/10 19:03:18 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
** If the cursor is not at the end of the string,
**	shift the string to the right to make space for the new character.
** Example: if we want to add the character 'M' to the following string:
** $>> abcdef
**      ^
** we will shift it right starting from the 'b'
** $>> a bcdef
** $>>  ^
*/

static void		shift_string_right(void)
{
	size_t	i;

	if (g_editor->cur_pos >= g_editor->cmd_sze)
		return ;
	i = g_editor->cmd_sze;
	while (i >= g_editor->cur_pos && i >= 1)
	{
		g_editor->cmd[i] = g_editor->cmd[i - 1];
		i--;
	}
}

void			add_char(char c)
{
	if (g_editor->cmd_sze < ARG_MAX)
	{
		command_erase();
		shift_string_right();
		g_editor->cmd[g_editor->cur_pos] = c;
		g_editor->cmd_sze++;
		command_write();
		move_cursor_right();
	}
}
