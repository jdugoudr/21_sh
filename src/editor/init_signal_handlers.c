/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:21:22 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 18:19:23 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h" // delete
#include "shell21.h"
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>

/*
** SIGWINCH: window resize signal
** Recalculate the terminal window dimensions.
*/

static void		handler_sigwinch(int signo)
{
	struct winsize	w;

	if (signo == SIGWINCH)
	{
		if ((ioctl(g_editor->tty_fd, TIOCGWINSZ, &w)) < 0)
			ft_exit("ioctl", 1, 1, EXIT_FAILURE);
		g_editor->win_height = w.ws_row;
		g_editor->win_width = w.ws_col;
	}
}

static void		handler_sigint(int signo)
{
	if (signo == SIGINT)
	{
		ft_dprintf(STDOUT_FILENO, "SIGINT CAUGHT\n");
		ft_exit(NULL, 1, 1, EXIT_FAILURE);
	}
}

void			init_signal_handlers(void)
{
	signal(SIGWINCH, handler_sigwinch);
	signal(SIGINT, handler_sigint);
}