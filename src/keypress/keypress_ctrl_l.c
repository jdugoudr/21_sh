/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_ctrl_l.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:53:55 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/24 18:14:37 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			keypress_ctrl_l(void)
{
	tputs(tgetstr("cl", NULL), g_editor->tty_fd, tputs_char);
	command_write();
}