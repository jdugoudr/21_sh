/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_default_conf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:08:25 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/03 14:46:01 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			restore_default_conf(void)
{
	if (g_editor->term == NULL || g_editor->oldterm == NULL)
		return ;
	g_editor->term->c_lflag |= (ICANON | ECHO);
	if (g_editor->oldterm != NULL)
		tcsetattr(g_editor->tty_fd, TCSANOW, g_editor->oldterm); // IN OR OUT?
	tputs(tgetstr("ei", NULL), 1, tputs_char);
}