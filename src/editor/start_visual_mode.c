/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_visual_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:23:40 by mdaoud            #+#    #+#             */
/*   Updated: 2019/07/01 18:45:58 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"
#include "keypress.h"
#include "shell21.h"

static void		right_key(size_t *start, size_t *end)
{
	if (g_editor->cur_pos == g_editor->cmd_sze)
		return ;
	if (g_editor->cur_pos == *end)
	{
		(*end)++;
		command_erase();
		g_editor->cur_pos++;
		write_in_visual(*start, *end);
	}
	else
	{
		(*start)++;
		command_erase();
		g_editor->cur_pos++;
		write_in_visual(*start, *end);
	}
}

static void		left_key(size_t *start, size_t *end)
{
	if (g_editor->cur_pos == 0)
		return ;
	if (g_editor->cur_pos == *start)
	{
		(*start)--;
		command_erase();
		g_editor->cur_pos--;
	}
	else
	{
		(*end)--;
		command_erase();
		g_editor->cur_pos--;
	}
	write_in_visual(*start, *end);
}

static void		exit_visual_mode(void)
{
	command_erase();
	command_write();
	if (g_editor->flag_sigint)
	{
		g_editor->flag_sigint = 0;
		while (g_editor->cur_pos < g_editor->cmd_sze)
			move_cursor_right();
		ft_dprintf(STDOUT_FILENO, "\n");
		g_shell->hist_ptr = NULL;
		command_reset();
		prompt_reset();
		prompt_display();
		g_editor->quotes = 0;
	}
	return ;
}

static int		dispatch_control(unsigned long touch, size_t *s, size_t *e)
{
	if (touch == CTRL_B_KEY)
		keypress_ctrl_b(*s, *e);
	else if (touch == CTRL_K_KEY)
		keypress_ctrl_k(*s, *e);
	else if (touch == CTRL_P_KEY)
		keypress_ctrl_p();
	else if (touch == CTRL_A_KEY)
	{
		command_erase();
		*s = 0;
		*e = g_editor->cmd_sze;
		g_editor->cur_pos = g_editor->cmd_sze;
		write_in_visual(*s, *e);
	}
	if (touch == CTRL_C_KEY)
	{
		g_editor->flag_sigint = 1;
		return (1);
	}
	if (touch == ESC_KEY || touch == CTRL_B_KEY || touch == CTRL_K_KEY
		|| touch == CTRL_P_KEY)
		return (1);
	return (0);
}

void			start_visual_mode(void)
{
	size_t			start;
	size_t			end;
	unsigned long	buf;

	end = g_editor->cur_pos;
	start = g_editor->cur_pos;
	while ((buf = reader()))
	{
		if (buf == LEFT_KEY)
			left_key(&start, &end);
		else if (buf == RIGHT_KEY)
			right_key(&start, &end);
		else
		{
			if (dispatch_control(buf, &start, &end))
				return (exit_visual_mode());
		}
	}
}
