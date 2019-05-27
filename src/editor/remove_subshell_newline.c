/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_subshell_newline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:27:48 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/27 18:46:10 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

void			remove_subshell_newline(void)
{
	size_t	i;
	size_t	pos;
	int		paranth_flag;

	i = 0;
	paranth_flag = 0;
	pos = g_editor->cur_pos;
	while (g_editor->cmd[i])
	{
		if (g_editor->cmd[i] == '(')
			paranth_flag = 1;
		if (g_editor->cmd[i] == ')' && paranth_flag)
			paranth_flag = 0;
		if (g_editor->cmd[i] == '\n' && paranth_flag)
			g_editor->cmd[i] = ' ';
		i++;
	}
	g_editor->cur_pos = pos;
}
