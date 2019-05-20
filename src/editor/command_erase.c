/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_erase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:44:06 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 17:53:05 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

void			get_max_line_count(void)
{
	size_t		tmp;

	if (!ft_strchr(g_editor->cmd, '\n'))
	{
		tmp = g_editor->cmd_sze + g_editor->offset;
		g_editor->max_line = tmp / g_editor->win_width;
		return ;
	}
	get_editor_dim();
}

void			command_erase(void)
{
	size_t	i;

	get_max_line_count();
	i = g_editor->line;
	while (i < g_editor->max_line)
	{
		tputs(tgetstr("do", NULL), 1, tputs_char);
		i++;
	}
	i = 0;
	while (i <= g_editor->max_line)
	{
		tputs(tgetstr("dl", NULL), 1, tputs_char);
		if (i < g_editor->max_line)
			tputs(tgetstr("up", NULL), 1, tputs_char);
		i++;
	}
	tputs(tgetstr("cr", NULL), 1, tputs_char);
}
