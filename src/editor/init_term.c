/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:53:28 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/23 17:08:10 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "shell21.h"
#include "sh_error.h"
#include <sys/ioctl.h>
#include "libft.h"

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

	if ((ret = isatty(g_editor->tty_fd)) < 0)
		ft_exit("Device is not a tty", 0, 1, EXIT_FAILURE);
	term_type = getenv("TERM");
	if (term_type == NULL)
		ft_exit("TERM environment variable is not set", 0, 1, EXIT_FAILURE);
	ret = tgetent(buf, term_type);
	if (ret == 0)
		ft_exit("Can't find TERM entry in terminfo base", 0, 1, EXIT_FAILURE);
	if (ret == -1)
		ft_exit("terminfo database could not be found", 0, 1, EXIT_FAILURE);
	if ((g_editor->term = malloc(sizeof(t_termios))) == NULL)
		ft_exit(INTERN_ERR, 0, 1, EXIT_FAILURE);
	if ((g_editor->oldterm = malloc(sizeof(t_termios))) == NULL)
		ft_exit(INTERN_ERR, 0, 1, EXIT_FAILURE);
	if ((tcgetattr(g_editor->tty_fd, g_editor->term)) < 0)
		ft_exit("tcgetattr", 0, 1, EXIT_FAILURE);
	if ((tcgetattr(g_editor->tty_fd, g_editor->oldterm)) < 0)
		ft_exit("tcgetattr", 0, 1, EXIT_FAILURE);
}

void			init_term(void)
{
	get_terminfo();
	set_terminfo();
}
