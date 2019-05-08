/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_shift_down.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 23:49:36 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/24 18:14:42 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

// void			keypress_shift_down(void)
// {
// 	size_t	i;

// 	if (g_editor->cur_pos + g_editor->win_width > g_editor->cmd_sze ||
// 		ft_strchr(g_editor->cmd, '\n'))
// 	{
// 		keypress_end();
// 		return ;
// 	}
// 	g_editor->cur_pos += g_editor->win_width;
// 	g_editor->line++;
// 	tputs(tgetstr("do", NULL), g_editor->tty_fd, tputs_char);
// 	tputs(tgetstr("cr", NULL), 1, tputs_char);
// 	i = 0;
// 	while (i < g_editor->col)
// 	{
// 		tputs(tgetstr("nd", NULL), 1, tputs_char);
// 		i++;
// 	}
// }

void			keypress_shift_down(void)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	while (i < g_editor->win_width)
	{
		move_cursor_right();
		if (g_editor->cmd[g_editor->cur_pos] == '\n')
		{
			if (flag)
				break ;
			else
				flag = 1;
		}
		i++;
	}
}