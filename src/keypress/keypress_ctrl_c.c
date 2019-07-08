/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_ctrl_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 18:57:45 by mdaoud            #+#    #+#             */
/*   Updated: 2019/07/08 10:43:31 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "keypress.h"
#include "libft.h"
#include "shell21.h"

void			keypress_ctrl_c(void)
{
	g_editor->flag_sigint = 1;
	while (g_editor->cur_pos < g_editor->cmd_sze)
		move_cursor_right();
	ft_dprintf(STDOUT_FILENO, "\n");
	g_shell->hist_ptr = NULL;
	command_reset();
	prompt_reset();
	prompt_display();
	g_editor->quotes = 0;
}
