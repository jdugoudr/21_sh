/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_keypress.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 22:06:31 by mdaoud            #+#    #+#             */
/*   Updated: 2019/07/02 18:20:32 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "editor.h"
#include "shell21.h"
#include <unistd.h>

static void		dispatch_arrow(unsigned long touch)
{
	if (touch == LEFT_KEY)
		move_cursor_left();
	else if (touch == RIGHT_KEY)
		move_cursor_right();
	if (touch == UP_KEY)
		keypress_uparrow();
	else if (touch == DOWN_KEY)
		keypress_downarrow();
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
	if (touch == CTRL_C_KEY)
		keypress_ctrl_c();
	if (touch == CTRL_L_KEY)
		keypress_ctrl_l();
	else if (touch == CTRL_P_KEY)
		keypress_ctrl_p();
	else if (touch == CTRL_R_KEY)
		start_search_mode();
	else if (touch == CTRL_U_KEY)
		keypress_ctrl_u();
	else if (touch == CTRL_W_KEY)
		start_visual_mode();
}

static void		dispatch_home_end(unsigned long touch)
{
	if (touch == HOME_KEY)
		keypress_home();
	else if (touch == END_KEY)
		keypress_end();
}

int				dispatch_keypress(unsigned long touch)
{
	if (touch == RET_KEY)
		return (1);
	else if (touch == CTRL_D_KEY && g_editor->cmd_sze == 0)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		ft_exit(NULL, 1, 1, EXIT_SUCCESS);
	}
	else if (touch == UP_KEY || touch == DOWN_KEY
		|| touch == LEFT_KEY || touch == RIGHT_KEY)
		dispatch_arrow(touch);
	else if (touch == SHIFT_UP_KEY || touch == SHIFT_DOWN_KEY
		|| touch == SHIFT_LEFT_KEY || touch == SHIFT_RIGHT_KEY)
		dispatch_shift(touch);
	else if (touch == CTRL_U_KEY || touch == CTRL_L_KEY || touch == CTRL_C_KEY
		|| touch == CTRL_R_KEY || touch == CTRL_W_KEY || touch == CTRL_P_KEY)
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
