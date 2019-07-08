/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:21:22 by mdaoud            #+#    #+#             */
/*   Updated: 2019/07/08 10:32:15 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"
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

void			init_signal_handlers(void)
{
	signal(SIGWINCH, handler_sigwinch);
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
