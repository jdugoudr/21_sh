/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_subshell_newline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:27:48 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/27 18:42:22 by mdaoud           ###   ########.fr       */
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

// void			remove_subshell_newline(void)
// {
// 	size_t	i;
// 	size_t	pos;

// 	i = 0;
// 	pos = g_editor->cur_pos;
// 	while (g_editor->cmd[i])
// 	{
// 		if (g_editor->cmd[i] == '(' && g_editor->cmd[i + 1] == '\n')
// 		{
// 			// ft_printf("cur is on \'%c\'\n", g_editor->cmd[g_editor->cur_pos]);
// 			// while (1);
// 			g_editor->cur_pos = i + 2;
// 			if (g_editor->cur_pos > g_editor->cmd_sze)
// 				return ;
// 			g_editor->cmd_sze--;
// 			shift_string_left();
// 		}
// 		else if (g_editor->cmd[i] == '\n' && g_editor->cmd[i + 1] == ')')
// 		{
// 			g_editor->cmd_sze--;
// 			g_editor->cur_pos = i + 1;
// 			shift_string_left();
// 		}
// 		i++;
// 	}
// 	g_editor->cur_pos = pos;
// }