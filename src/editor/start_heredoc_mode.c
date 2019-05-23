/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_heredoc_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:13:25 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/23 19:38:06 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"
#include "keypress.h"
#include <signal.h>
#include "sh_error.h"

static void		init_heredoc_mode(char *line, char buf[], int *done)
{
	line = NULL;
	init_term();
	ft_bzero(buf, READ_BUF_SZE + 1);
	command_reset();
	prompt_set("heredoc> ");
	*done = 0;
}

static char		*handle_read_error(char **line)
{
	ft_dprintf(STDERR_FILENO, INTERN_ERR);
	if (line)
		free(line);
	return (NULL);
}

static void		process_keypress(int ret, int *done, char **line, char *end_here)
{
	if (ret == 1)
	{
		if (ft_strequ(end_here, g_editor->cmd))
		{
			*done = 1;
			return ;
		}
		if (*line == NULL)
			*line = ft_strdup(g_editor->cmd);
		else
			*line = ft_strjoin(*line, g_editor->cmd, 1);
		*line = ft_strjoin(*line, "\n", 1);
	}
	else if (ret == -1)
	{
		{
			g_editor->flag_sigint = 0;
			free(*line);
			*done = 1;
		}
	}
}
char			*start_heredoc_mode(char *end_here)
{
	char	*line;
	char	buf[READ_BUF_SZE + 1];
	int		ret;
	int		done;

	line = NULL;
	init_heredoc_mode(line, buf, &done);
	while (!done)
	{
		prompt_display();
		while ((ret = read(STDIN_FILENO, buf, READ_BUF_SZE)) != 0)
		{
			if (ret < 0)
				return (handle_read_error(&line));
			ret = dispatch_heredoc_key(*(unsigned long *)buf);
			process_keypress(ret, &done, &line, end_here);
			if (ret == 1 || ret == -1)
				break ;
			ft_bzero(buf, READ_BUF_SZE + 1);
		}
		command_reset();
		ft_dprintf(g_editor->tty_fd, "\n");
	}
	return (line);
}