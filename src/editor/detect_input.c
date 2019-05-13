/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 22:30:12 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/13 15:23:09 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "editor.h"
#include "parser.h"
#include "shell21.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/ioctl.h>
#include "keypress.h"
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
	ft_dprintf(g_editor->tty_fd, "\n");
	restore_default_conf();
	parser(g_editor->cmd);
	set_terminfo();
	history_append(g_editor->cmd);
	command_reset();
	prompt_reset();
	g_shell->hist_ptr = NULL;
	ft_memset(buf, '\0', READ_BUF_SZE);
	if (!ends_with_newline())
		ft_dprintf(g_editor->tty_fd, "\033[7m%%\033[m\n");
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
			ft_exit("read", 1, 1, EXIT_FAILURE) ;
		else
		{
			ret = dispatch_keypress(*(unsigned long *)buf);
			if (ret > 0)
			{
				if (!expression_balanced())
				{
					ft_strcat(g_editor->cmd, "\n");
					ft_strcat(cmd_line, g_editor->cmd);
					continue_until_balanced();
				}
				else
				{
					ft_strcat(cmd_line, g_editor->cmd);
					command_set(cmd_line, 0);
					end_of_input(buf, cmd_line);
				}
				break ;
			}
			ft_memset(buf, '\0', READ_BUF_SZE);
			continue ;
		}
	}
}
