/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_heredoc_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:13:25 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/28 16:17:40 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"
#include "keypress.h"
#include <signal.h>
#include "sh_error.h"

static void		init_heredoc_mode(char **line, char buf[], int *done)
{
	*line = NULL;
	set_terminfo();
	g_editor->term->c_lflag &= ~ISIG;
	tcsetattr(g_editor->tty_fd, TCSANOW, g_editor->term);
	ft_bzero(buf, READ_BUF_SZE + 1);
	command_reset();
	prompt_set("heredoc> ");
	*done = 0;
}

static char		*heredoc_intern_error(char **line)
{
	ft_dprintf(STDERR_FILENO, INTERN_ERR);
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
	else if (ret == -1 || ret == -2)
	{
		ft_strdel(line);
		*done = 1;
	}
}

static char		*exit_heredoc_mode(char *line)
{
	g_editor->term->c_lflag |= ISIG;
	tcsetattr(g_editor->tty_fd, TCSANOW, g_editor->term);
	return (line);
}

char			*start_heredoc_mode(char *end_here)
{
	char	*line;
	char	buf[READ_BUF_SZE + 1];
	int		ret;
	int		done;

	init_heredoc_mode(&line, buf, &done);
	while (!done)
	{
		prompt_display();
		while ((ret = read(STDIN_FILENO, buf, READ_BUF_SZE)) != 0)
		{
			if (ret < 0)
				return (heredoc_intern_error(&line));
			ret = dispatch_heredoc_key(*(unsigned long *)buf);
			process_keypress(ret, &done, &line, end_here);
			if (ret == 1 || ret == -1 || ret == -2)
				break ;
			ft_bzero(buf, READ_BUF_SZE + 1);
		}
		command_reset();
		ft_dprintf(g_editor->tty_fd, "\n");
	}
	return (exit_heredoc_mode(line));
}
