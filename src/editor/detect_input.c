/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 22:30:12 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/13 04:11:44 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "parser.h"
#include "shell21.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/ioctl.h>
#include "keypress.h"
#include <signal.h>
#include "sh_error.h"

/*
** This function will print a '%' in reverse video mode if
**	the output of a command is not terminated by a '\n'.
*/

static void			end_with_newline(void)
{
	ft_dprintf(g_editor->tty_fd, "\033[7m%%\033[m");
	ft_dprintf(g_editor->tty_fd, "%*c", g_editor->win_width - 1, ' ');
	tputs(tgetstr("dl", NULL), 1, tputs_char);
	tputs(tgetstr("cr", NULL), 1, tputs_char);
}

/*
** The function that will be executed once the user presses "Enter"
*/

static void			end_of_input(void)
{
	if (is_empty_cmd())
		return ;
	history_append(g_editor->cmd);
	ft_dprintf(g_editor->tty_fd, "\n");
	restore_default_conf();
	signal(SIGINT, handler_sigint_process);
	remove_subshell_newline();
	parser(ft_strdup(g_editor->cmd));
	init_signal_handlers();
	set_terminfo();
	command_reset();
	prompt_reset();
	g_shell->hist_ptr = NULL;
	end_with_newline();
	g_editor->flag_sigint = 0;
}

static void			unbalance_exp_handler(char *cmd_line)
{
	ft_strcat(g_editor->cmd, "\n");
	ft_strcat(cmd_line, g_editor->cmd);
	continue_until_balanced();
}

static void			set_up_for_execution(char *cmd_line)
{
	size_t		pos;

	if (g_editor->flag_sigint)
		ft_bzero(cmd_line, ARG_MAX);
	pos = g_editor->cur_pos + ft_strlen(cmd_line);
	ft_strcat(cmd_line, g_editor->cmd);
	command_set(cmd_line, 0);
	g_editor->cur_pos = pos;
	while (g_editor->cur_pos < g_editor->cmd_sze)
		move_cursor_right();
	ft_memset(cmd_line, '\0', ARG_MAX);
	end_of_input();
}

void				detect_input(void)
{
	static char	cmd_line[ARG_MAX] = {'\0'};
	long		ret;

	while (1)
	{
		if ((ret = reader()) == 0)
			continue ;
		if (ret < 0)
		{
			ft_dprintf(STDERR_FILENO, INTERN_ERR);
			ft_dprintf(g_editor->tty_fd, "\n");
			command_reset();
			break ;
		}
		ret = dispatch_keypress(ret);
		if (ret > 0)
		{
			if (!expression_balanced())
				unbalance_exp_handler(cmd_line);
			else
				set_up_for_execution(cmd_line);
			break ;
		}
	}
}
