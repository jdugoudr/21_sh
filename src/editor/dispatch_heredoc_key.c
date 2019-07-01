/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_heredoc_key.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 17:00:36 by mdaoud            #+#    #+#             */
/*   Updated: 2019/07/01 18:56:32 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "keypress.h"

static void		dispatch_arrow(unsigned long touch)
{
	if (touch == LEFT_KEY)
		move_cursor_left();
	else if (touch == RIGHT_KEY)
		move_cursor_right();
}

static void		dispatch_shift(unsigned long touch)
{
	if (touch == SHIFT_LEFT_KEY)
		keypress_shift_left();
	else if (touch == SHIFT_RIGHT_KEY)
		keypress_shift_right();
	else if (touch == SHIFT_UP_KEY)
		keypress_shift_up();
	else if (touch == SHIFT_DOWN_KEY)
		keypress_shift_down();
}

static void		dispatch_ctrl(unsigned long touch)
{
	if (touch == CTRL_L_KEY)
		keypress_ctrl_l();
	else if (touch == CTRL_U_KEY)
		keypress_ctrl_u();
}

static void		dispatch_home_end(unsigned long touch)
{
	if (touch == HOME_KEY)
		keypress_home();
	else if (touch == END_KEY)
		keypress_end();
}

int				dispatch_heredoc_key(unsigned long touch)
{
	if (touch == RET_KEY)
		return (1);
	else if (touch == CTRL_C_KEY)
		return (-1);
	else if (touch == CTRL_D_KEY && g_editor->cmd_sze == 0)
		return (-2);
	else if (touch == LEFT_KEY || touch == RIGHT_KEY)
		dispatch_arrow(touch);
	else if (touch == SHIFT_UP_KEY || touch == SHIFT_DOWN_KEY
		|| touch == SHIFT_LEFT_KEY || touch == SHIFT_RIGHT_KEY)
		dispatch_shift(touch);
	else if (touch == CTRL_U_KEY || touch == CTRL_L_KEY)
		dispatch_ctrl(touch);
	else if (touch == BCKSPCE_KEY)
		keypress_backspace();
	else if (touch == DEL_KEY)
		keypress_delete();
	else if (touch == HOME_KEY || touch == END_KEY)
		dispatch_home_end(touch);
	else if (touch >= ' ' && touch <= '~')
		add_char(touch);
	return (0);
}
