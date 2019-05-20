/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_shift_down.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 23:49:36 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 18:19:39 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "editor.h"

void			keypress_shift_down(void)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	while (i < g_editor->win_width)
	{
		if (g_editor->cmd[g_editor->cur_pos] == '\n')
		{
			if (flag)
				break ;
			else
				flag = 1;
		}
		move_cursor_right();
		i++;
	}
}
