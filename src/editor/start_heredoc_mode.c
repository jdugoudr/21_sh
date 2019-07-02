/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_heredoc_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:13:25 by mdaoud            #+#    #+#             */
/*   Updated: 2019/07/02 18:11:05 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"
#include "keypress.h"
#include <signal.h>
#include "sh_error.h"

static void		init_heredoc_mode(char **line, int *done)
{
	*line = NULL;
	set_terminfo();
	command_reset();
	prompt_set("heredoc> ");
	*done = 0;
}

static char		*heredoc_intern_error(char **line)
{
	char	msg[100];

	ft_strcpy(msg, "\n21sh: An intern issue appeared. Please try again.");
	ft_dprintf(STDERR_FILENO, msg);
	if (*line)
		free(*line);
	return (NULL);
}

static void		process_keypress(int ret, int *done, char **line, char *end)
{
	char	*tmp;

	if (ret == 1)
	{
		if (ft_strequ(end, g_editor->cmd))
			*done = 1;
		else
		{
			if (*line == NULL)
				tmp = ft_strdup(g_editor->cmd);
			else
				tmp = ft_strjoin(*line, g_editor->cmd, 1);
			if (tmp == NULL || (tmp = ft_strjoin(tmp, "\n", 1)) == NULL)
				heredoc_intern_error(line);
			else
				*line = tmp;
		}
	}
	else if (ret < 0)
	{
		*done = 1;
		if (ret == -1)
			ft_strdel(line);
	}
}

char			*start_heredoc_mode(char *end_here)
{
	char	*line;
	long	ret;
	int		done;

	init_heredoc_mode(&line, &done);
	while (!done)
	{
		prompt_display();
		while ((ret = reader()))
		{
			if (ret < 0)
				return (heredoc_intern_error(&line));
			ret = dispatch_heredoc_key(ret);
			process_keypress(ret, &done, &line, end_here);
			if (ret == 1 || ret == -1 || ret == -2)
				break ;
		}
		command_reset();
		ft_dprintf(g_editor->tty_fd, "\n");
	}
	return (line);
}
