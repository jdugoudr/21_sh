/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 17:44:49 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/30 17:50:15 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			command_set(char *str, int rewrite_flag)
{
	command_reset();
	ft_strcpy(g_editor->cmd, str);
	g_editor->cur_pos = ft_strlen(str);
	g_editor->cmd_sze = ft_strlen(str);
	if (rewrite_flag)
		rewrite_lines();
}