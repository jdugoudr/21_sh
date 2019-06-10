/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_shift_up.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 23:49:36 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/10 18:47:42 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "editor.h"
#include "libft.h"

void			keypress_shift_up(void)
{
	size_t		i;

	i = 0;
	if (g_editor->line == 0
		|| (g_editor->line == 1 && g_editor->col <= g_editor->offset))
	{
		if (!ft_strchr(g_editor->cmd, '\n'))
		{
			keypress_home();
			return ;
		}
	}
	i = 0;
	while (i < g_editor->win_width)
	{
		move_cursor_left();
		if (g_editor->cmd[g_editor->cur_pos] == '\n')
			break ;
		i++;
	}
}
