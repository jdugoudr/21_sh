/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_home.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:18:09 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/28 13:44:33 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			move_cursor_home(void)
{
	size_t	i;
	int		col0;

	i = 0;
	col0 = g_editor->col == g_editor->win_width;
	while (i < g_editor->max_line - col0)
	{
		tputs(tgetstr("up", NULL), 1, tputs_char);
		i++;
	}
	tputs(tgetstr("cr", NULL), 1, tputs_char);
}