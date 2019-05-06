/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:21:22 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/30 19:15:30 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include <signal.h>
#include <sys/ioctl.h>

/*
** SIGWINCH: window resize signal
** Recalculate the terminal window dimensions.
** Repostion the cursor properly after the window resize.
** Rewrite the command lines(s).
*/

static void		handler_sigwinch(int signo)
{
	struct winsize	w;
	int				x;

	if (signo == SIGWINCH)
	{
		if ((ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) < 0)
			ft_exit("ioctl", 1, EXIT_FAILURE);
		g_editor->win_height = w.ws_row;
		g_editor->win_width = w.ws_col;
		x = g_editor->cmd_sze - g_editor->win_width + g_editor->offset;
		x = (x < 0 ? 0 : x);
		g_editor->max_line = x / g_editor->win_width;
		if (x % g_editor->win_width)
			g_editor->max_line++;
		x = g_editor->cur_pos + g_editor->offset;
		g_editor->line = x / g_editor->win_width;
		g_editor->col = x % g_editor->win_width;
		rewrite_lines();
	}
}

static void		handler_sigint(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("SIGINT CAUGHT\n");
		ft_exit(NULL, 0, EXIT_FAILURE);
	}
}

void			init_signal_handlers(void)
{
	signal(SIGWINCH, handler_sigwinch);
	signal(SIGINT, handler_sigint);
}