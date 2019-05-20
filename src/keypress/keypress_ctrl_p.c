/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_ctrl_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:41:43 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 18:13:46 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "editor.h"

static void		paste(char *str)
{
	size_t	tmp;

	tmp = g_editor->cur_pos;
	command_set(str, 0);
	g_editor->cur_pos = tmp;
	command_write();
}

void			keypress_ctrl_p(void)
{
	size_t	i;
	size_t	j;
	char	str[ARG_MAX + 1];

	if (g_editor->cpy_buff[0] == '\0')
		return ;
	command_erase();
	i = -1;
	while (++i < g_editor->cur_pos)
		str[i] = g_editor->cmd[i];
	i = 0;
	j = g_editor->cur_pos;
	while (g_editor->cpy_buff[i])
	{
		str[g_editor->cur_pos] = g_editor->cpy_buff[i];
		g_editor->cur_pos++;
		i++;
	}
	i = g_editor->cur_pos;
	while (g_editor->cmd[j])
		str[i++] = g_editor->cmd[j++];
	str[i] = '\0';
	paste(str);
}
