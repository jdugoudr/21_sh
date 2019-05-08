/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 22:30:12 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/08 17:14:04 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "parser.h"
#include <sys/ioctl.h>

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

static void			end_of_input(t_shell *shell, char buf[], char line[])
{
	ft_memset(line, '\0', ARG_MAX);
	if (is_empty_cmd())
	{
		dprintf(g_editor->tty_fd, "\n");
		command_reset();
		ft_memset(buf, '\0', READ_BUF_SZE);
		return ;
	}
	keypress_end();
	dprintf(g_editor->tty_fd, "\n");
	restore_default_conf();
	parser(g_editor->cmd, shell);
	set_terminfo();
	history_append(shell, g_editor->cmd);
	command_reset();
	prompt_reset();
	shell->hist_ptr = NULL;
	ft_memset(buf, '\0', READ_BUF_SZE);
}

static void			continue_until_quote(void)
{
	if (g_editor->quotes == 1)
		prompt_set("quote> ");
	else
		prompt_set("dquote> ");
	dprintf(g_editor->tty_fd, "\n");
	command_reset();
}

void				detect_input(t_shell *shell)
{
	char		buf[READ_BUF_SZE];
	static char	cmd_line[ARG_MAX] = {'\0'};
	int			ret;

	ft_memset(buf, '\0', READ_BUF_SZE);
	while ((ret = read(STDIN_FILENO, buf, 7)) != 0)
	{
		if (ret == -1)
			ft_exit("read", 1, 1, EXIT_FAILURE) ;
		else
		{
			ret = dispatch_keypress(shell, *(unsigned long *)buf);
			if (ret > 0)
			{
				if (!quotes_balanced())
				{
					ft_strcat(g_editor->cmd, "\n");
					ft_strcat(cmd_line, g_editor->cmd);
					continue_until_quote();
				}
				else
				{
					// dprintf(g_editor->tty_fd, "\nline: %d\tcol: %d\tmax lines: %d\n", g_editor->line, g_editor->col, g_editor->max_line);
					// dprintf(g_editor->tty_fd, "Size: %d\tpos: %d\n", g_editor->cmd_sze, g_editor->cur_pos);
					// dprintf(g_editor->tty_fd, "Width: %d\tHeight: %d\n", g_editor->win_width, g_editor->win_height);
					ft_strcat(cmd_line, g_editor->cmd);
					command_set(cmd_line, 0);
					end_of_input(shell, buf, cmd_line);
				}
				break ;
			}
			ft_memset(buf, '\0', READ_BUF_SZE);
			continue ;
		}
	}
}