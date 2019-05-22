/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_heredoc_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:13:25 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/22 15:52:58 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"
#include "keypress.h"

static void		dispatch_arrow(unsigned long touch)
{
	if (touch == LEFT_KEY)
		move_cursor_left();
	else if (touch == RIGHT_KEY)
		move_cursor_right();
}

static void		dispatch_shift(unsigned long touch)
{
	if (touch == SHIFT_LEFT_KEY)
		keypress_shift_left();
	else if (touch == SHIFT_RIGHT_KEY)
		keypress_shift_right();
	else if (touch == SHIFT_UP_KEY)
		keypress_shift_up();
	else if (touch == SHIFT_DOWN_KEY)
		keypress_shift_down();
}

static void		dispatch_ctrl(unsigned long touch)
{
	if (touch == CTRL_L_KEY)
		keypress_ctrl_l();
	else if (touch == CTRL_U_KEY)
		keypress_ctrl_u();
}

static void		dispatch_home_end(unsigned long touch)
{
	if (touch == HOME_KEY)
		keypress_home();
	else if (touch == END_KEY)
		keypress_end();
}

static int				dispatch_heredoc_key(unsigned long touch)
{
	if (touch == RET_KEY)
		return (1);
	else if (touch == CTRL_D_KEY && g_editor->cmd_sze == 0)
		return (0);
	else if (touch == LEFT_KEY || touch == RIGHT_KEY)
		dispatch_arrow(touch);
	else if (touch == SHIFT_UP_KEY || touch == SHIFT_DOWN_KEY ||\
		touch == SHIFT_LEFT_KEY || touch == SHIFT_RIGHT_KEY)
		dispatch_shift(touch);
	else if (touch == CTRL_U_KEY || touch == CTRL_L_KEY)
		dispatch_ctrl(touch);
	else if (touch == BCKSPCE_KEY)
		keypress_backspace();
	else if (touch == DEL_KEY)
		keypress_delete();
	else if (touch == HOME_KEY || touch == END_KEY)
		dispatch_home_end(touch);
	else if (touch >= ' ' && touch <= '~')
		add_char(touch);
	return (0);
}

static void		handler_sigint_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		g_editor->flag_sigint = 1;
		init_term();
		command_reset();
		prompt_reset();
		ft_dprintf(g_editor->tty_fd, "\n");
	}
}

char			*start_heredoc_mode(char *end_here)
{
	char	*line;
	char	buf[READ_BUF_SZE + 1];
	int		ret;
	int		done;

	line = NULL;
	init_term();
	ft_bzero(buf, READ_BUF_SZE + 1);
	command_reset();
	prompt_set("heredoc> ");
	signal(SIGINT, handler_sigint_heredoc);
	done = 0;
	while (!done && !g_editor->flag_sigint)
	{
		prompt_display();
		while ((ret = read(STDIN_FILENO, buf, READ_BUF_SZE)) != 0)
		{
			if (ret < 0)
			{
				free(line);
				break ;
			}
			ret = dispatch_heredoc_key(*(unsigned long *)buf);
			ft_bzero(buf, READ_BUF_SZE + 1);
			if (ret == 1)
			{
				if (ft_strequ(end_here, g_editor->cmd))
				{
					done = 1;
					break ;
				}
				if (line == NULL)
					line = ft_strdup(g_editor->cmd);
				else
					line = ft_strjoin(line, g_editor->cmd, 1);
				line = ft_strjoin(line, "\n", 1);
				break ;
			}
		}
		command_reset();
		ft_dprintf(g_editor->tty_fd, "\n");
	}
	prompt_reset();
	restore_default_conf();
	if (g_editor->flag_sigint)
	{
		free(line);
		return (NULL);
	}
	return (line);
}