/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_keypress.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 22:06:31 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/30 15:14:17 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static void		dispatch_arrow(t_shell *shell, unsigned long touch)
{
	if (touch == LEFT_KEY)
		keypress_leftarrow();
	else if (touch == RIGHT_KEY)
		keypress_rightarrow();
	if (touch == UP_KEY)
		keypress_uparrow(shell);
	else if (touch == DOWN_KEY)
		keypress_downarrow(shell);
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

static void		dispatch_ctrl(t_shell *shell, unsigned long touch)
{
	(void)shell;
	if (touch == CTRL_U_KEY)
		keypress_ctrl_u();
	else if (touch == CTRL_L_KEY)
		keypress_ctrl_l();
	else if (touch == CTRL_R_KEY)
		keypress_ctrl_r(shell);
}

int				dispatch_keypress(t_shell *shell, unsigned long touch)
{
	if (touch == RET_KEY)
		return (1);
	else if (touch == ESC_KEY)
		ft_exit(NULL, 1, EXIT_SUCCESS);
	else if (touch == UP_KEY || touch == DOWN_KEY ||\
		touch == LEFT_KEY || touch == RIGHT_KEY)
		dispatch_arrow(shell, touch);
	else if (touch == SHIFT_UP_KEY || touch == SHIFT_DOWN_KEY ||\
		touch == SHIFT_LEFT_KEY || touch == SHIFT_RIGHT_KEY)
		dispatch_shift(touch);
	else if (touch == CTRL_U_KEY || touch == CTRL_L_KEY || touch == CTRL_R_KEY)
		dispatch_ctrl(shell, touch);
	else if (touch == BCKSPCE_KEY)
		keypress_backspace();
	else if (touch == DEL_KEY)
		keypress_delete();
	else if (touch == HOME_KEY)
		keypress_home();
	else if (touch == END_KEY)
		keypress_end();
	else
		add_char(touch);
	// else
	// 	ft_printf("%#lX\n", touch);
	return (0);
}
