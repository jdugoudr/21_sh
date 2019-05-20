/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:51:34 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 17:51:35 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

void			command_append(char *str, int rewrite_flag)
{
	if (rewrite_flag)
		command_erase();
	ft_strcat(g_editor->cmd, str);
	g_editor->cmd_sze = ft_strlen(g_editor->cmd);
	g_editor->cur_pos = ft_strlen(g_editor->cmd);
	if (rewrite_flag)
		command_write();
}
