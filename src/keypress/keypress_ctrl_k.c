/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_ctrl_k.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:41:43 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 18:20:49 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "editor.h"
#include "libft.h"

static void		do_cut(char *str)
{
	size_t	tmp;

	tmp = g_editor->cur_pos;
	command_set(str, 0);
	g_editor->cur_pos = tmp;
	command_write();
}

static void		copy_to_buffer(size_t start, size_t end)
{
	char	tmp[ARG_MAX + 1];
	size_t	i;

	if (start == end)
		return ;
	ft_memset(g_editor->cpy_buff, '\0', ARG_MAX + 1);
	ft_memset(tmp, '\0', ARG_MAX + 1);
	i = 0;
	while (start < end)
	{
		tmp[i] = g_editor->cmd[start];
		start++;
		i++;
	}
	ft_strcpy(g_editor->cpy_buff, tmp);
}

static void		update_cur_pos(size_t start, size_t end)
{
	if (g_editor->cur_pos == start)
		return ;
	if (g_editor->cur_pos == end && g_editor->cmd - end + start >= 0)
		g_editor->cur_pos = g_editor->cur_pos - end + start;
	else if (g_editor->cur_pos == end)
		g_editor->cur_pos = 0;
}

void			keypress_ctrl_k(size_t start, size_t end)
{
	char	str[ARG_MAX + 1];
	size_t	i;

	if (start == end)
		return ;
	command_erase();
	update_cur_pos(start, end);
	copy_to_buffer(start, end);
	i = 0;
	while (i < start)
	{
		str[i] = g_editor->cmd[i];
		i++;
	}
	while (end < g_editor->cmd_sze)
	{
		str[i] = g_editor->cmd[end];
		i++;
		end++;
	}
	str[i] = '\0';
	do_cut(str);
}
