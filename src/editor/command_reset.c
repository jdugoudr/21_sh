/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_reset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:21:39 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/29 15:27:56 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			command_reset(void)
{
	ft_bzero(g_editor->cmd, ARG_MAX);
	g_editor->max_line = 0;
	g_editor->line = 0;
	g_editor->col = g_editor->offset;
	g_editor->cmd_sze = 0;
	g_editor->cur_pos = 0;
	// g_editor->quotes = 0;	// ?
}