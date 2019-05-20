/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_reset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:51:51 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 17:51:53 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

void			command_reset(void)
{
	ft_bzero(g_editor->cmd, ARG_MAX);
	g_editor->max_line = 0;
	g_editor->line = 0;
	g_editor->col = g_editor->offset;
	g_editor->cmd_sze = 0;
	g_editor->cur_pos = 0;
}
