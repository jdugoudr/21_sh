/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:52:04 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 17:52:05 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

void			command_set(char *str, int rewrite_flag)
{
	if (rewrite_flag)
		command_erase();
	command_reset();
	ft_strcpy(g_editor->cmd, str);
	g_editor->cur_pos = ft_strlen(str);
	g_editor->cmd_sze = ft_strlen(str);
	if (rewrite_flag)
		command_write();
}
