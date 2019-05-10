/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminfo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:47:50 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 15:14:01 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

/*
** Modify the termio structure to our needs.
** Put the termios in NON-CANNONICAL mode.
** Remove the ECHO flag.
** Put the terminal in "insertion mode".
** ISIG: When any of the characters INTR, QUIT, SUSP, or DSUSP are received,
**	generate the corresponding signal.
*/

void		set_terminfo(void)
{
	g_editor->term->c_lflag &= ~(ICANON | ECHO);
	g_editor->term->c_lflag |= ISIG;
	g_editor->term->c_cc[VMIN] = 1;
	g_editor->term->c_cc[VTIME] = 0;
	tcsetattr(g_editor->tty_fd, TCSANOW, g_editor->term);	//add error check
	tputs(tgetstr("im", NULL), 1, tputs_char);
}