/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_default_conf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:08:25 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/07 17:17:23 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			restore_default_conf(void)
{
	g_editor->term->c_lflag |= (ICANON | ECHO);
	if (g_editor->oldterm != NULL)
		tcsetattr(STDOUT_FILENO, TCSANOW, g_editor->oldterm);
	tputs(tgetstr("ei", NULL), 1, tputs_char);
}