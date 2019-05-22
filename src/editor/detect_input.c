/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 22:30:12 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/22 15:46:40 by mdaoud           ###   ########.fr       */
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

/*
** Check if a command only exists of spaces and tabulations
*/

static int			is_empty_cmd(void)
{
	size_t	i;

	i = 0;
	while (g_editor->cmd[i] != '\0')
	{
		if (g_editor->cmd[i] != ' ' || g_editor->cmd[i] <= '\t')
			return (0);
		i++;
	}
	return (1);
}

/*
** The function that will be executed once the user presses "Enter"
*/

static void			end_of_input(char buf[], char line[])
{
	ft_memset(line, '\0', ARG_MAX);
	if (is_empty_cmd())
	{
		ft_dprintf(g_editor->tty_fd, "\n");
		command_reset();
		ft_memset(buf, '\0', READ_BUF_SZE);
		return ;
	}
	while (g_editor->cur_pos < g_editor->cmd_sze)
		move_cursor_right();
	history_append(g_editor->cmd);
	ft_dprintf(g_editor->tty_fd, "\n");
	restore_default_conf();
	signal(SIGINT, handler_sigint_process);
	parser(g_editor->cmd);
	init_signal_handlers();
	set_terminfo();
	command_reset();
	prompt_reset();
	g_shell->hist_ptr = NULL;
	ft_memset(buf, '\0', READ_BUF_SZE);
	if (!ends_with_newline() && !g_editor->flag_sigint)
		ft_dprintf(g_editor->tty_fd, "\033[7m%%\033[m\n");
	g_editor->flag_sigint = 0;
}

static void			unbalance_exp_handler(char *cmd_line)
{
	ft_strcat(g_editor->cmd, "\n");
	ft_strcat(cmd_line, g_editor->cmd);
	continue_until_balanced();
}

static void			set_up_for_execution(char *cmd_line, char buf[])
{
	size_t		pos;

	if (g_editor->flag_sigint)
		ft_bzero(cmd_line, ARG_MAX);
	pos = g_editor->cur_pos + ft_strlen(cmd_line);
	ft_strcat(cmd_line, g_editor->cmd);
	command_set(cmd_line, 0);
	g_editor->cur_pos = pos;
	end_of_input(buf, cmd_line);
}

void				detect_input(void)
{
	char		buf[READ_BUF_SZE];
	static char	cmd_line[ARG_MAX] = {'\0'};
	int			ret;

	ft_memset(buf, '\0', READ_BUF_SZE);
	while ((ret = read(STDIN_FILENO, buf, READ_BUF_SZE - 1)) != 0)
	{
		if (ret == -1)
			ft_exit("read", 1, 1, EXIT_FAILURE);
		ret = dispatch_keypress(*(unsigned long *)buf);
		if (ret > 0)
		{
			if (!expression_balanced())
				unbalance_exp_handler(cmd_line);
			else
				set_up_for_execution(cmd_line, buf);
			break ;
		}
		ft_memset(buf, '\0', READ_BUF_SZE);
		continue ;
	}
}
