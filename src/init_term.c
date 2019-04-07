/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:53:28 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/28 13:44:33 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell21.h"
#include <sys/ioctl.h>

/*
** Checks if the device is a terminal.
** Save the terminal info in 'term' variable for further moification.
** Save the terminal info in 'oldterm' variable to restore it at the end.
*/

static void		get_terminfo(void)
{
	int		ret;
	char	*term_type;
	char	buf[2048];

	if ((ret = isatty(STDOUT_FILENO)) < 0)
		ft_exit("Device is not a tty", 1, EXIT_FAILURE);
	term_type = getenv("TERM");
	if (term_type == NULL)
		ft_exit("TERM environment variable is not set", 1, EXIT_FAILURE);
	ret = tgetent(buf, term_type);
	if (ret == 0)
		ft_exit("Can't find TERM entry in terminfo base", 1, EXIT_FAILURE);
	if (ret == -1)
		ft_exit("terminfo database could not be found", 1, EXIT_FAILURE);
	if ((g_editor->term = malloc(sizeof(t_termios))) == NULL)
		ft_exit("malloc", 1, EXIT_FAILURE);
	if ((g_editor->oldterm = malloc(sizeof(t_termios))) == NULL)
		ft_exit("malloc", 1, EXIT_FAILURE);
	if ((tcgetattr(STDOUT_FILENO, g_editor->term)) < 0)
		ft_exit("tcgetattr", 1, EXIT_FAILURE);
	if ((tcgetattr(STDOUT_FILENO, g_editor->oldterm)) < 0)
		ft_exit("tcgetattr", 1, EXIT_FAILURE);
}

/*
** Modify the termio structure to our needs.
** Put the termios in NON-CANNONICAL mode.
** Remove the ECHO flag.
** Put the terminal in "insert mode".
** ISIG: When any of the characters INTR, QUIT, SUSP, or DSUSP are received,
**	generate the corresponding signal.
*/

static void		set_terminfo(void)
{
	g_editor->term->c_lflag &= ~(ICANON | ECHO);
	g_editor->term->c_lflag |= ISIG;
	// g_editor->term->c_oflag |= OPOST;
	g_editor->term->c_cc[VMIN] = 1;
	g_editor->term->c_cc[VTIME] = 0;
	tcsetattr(STDERR_FILENO, 0, g_editor->term);	//add error check
	tputs(tgetstr("im", NULL), 1, tputs_char);
}

/*
** Initialise our shell structure.
** Get the width and height of the terminal window.
*/

static void		set_shellinfo(void)
{
	struct winsize w;

	if ((ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) < 0)
		ft_exit("ioctl", 1, EXIT_FAILURE);
	g_editor->win_height = w.ws_row;
	g_editor->win_width = w.ws_col;
	ft_bzero(g_editor->cmd, ARG_MAX);
	g_editor->offset = 4;
	g_editor->col = g_editor->offset;
	g_editor->line = 0;
	g_editor->max_line = 0;
	g_editor->cur_pos = 0;
	g_editor->cmd_sze = 0;
}

void			init_term(void)
{
	get_terminfo();
	set_terminfo();
	set_shellinfo();
}