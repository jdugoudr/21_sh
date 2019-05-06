/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 17:48:04 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/30 17:49:00 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			command_append(char *str, int rewrite_flag)
{
	ft_strcat(g_editor->cmd, str);
	g_editor->cmd_sze = ft_strlen(g_editor->cmd);
	g_editor->cur_pos = ft_strlen(g_editor->cmd);
	if (rewrite_flag)
		rewrite_lines();
}