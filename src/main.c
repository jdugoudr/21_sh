/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:29:25 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/29 16:08:39 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "libft.h"
#include "sh_error.h"
#include "editor.h"
#include <sys/ioctl.h>
#include "parser.h"
#include "shell21.h"
#include <fcntl.h>

static void			init_env(char **environ)
{
	char	**env;
	int		count;

	count = 0;
	while (environ[count] != NULL)
		count++;
	if ((env = malloc(sizeof(char *) * (count + 1))) == NULL)
		ft_exit(INTERN_ERR, 0, 1, EXIT_FAILURE);
	env[count] = NULL;
	count = 0;
	while (environ[count] != NULL)
	{
		if ((env[count] = ft_strdup(environ[count])) == NULL)
		{
			while (count-- > 0)
				free(env[count]);
			free(env);
			ft_exit(INTERN_ERR, 0, 1, EXIT_FAILURE);
		}
		count++;
	}
	g_shell->env = env;
}

static t_shell		*init_shell(char **enviro)
{
	if ((g_shell = malloc(sizeof(t_shell))) == NULL)
		ft_exit(INTERN_ERR, 0, 1, EXIT_FAILURE);
	g_shell->hist = NULL;
	g_shell->hist_ptr = NULL;
	if (enviro == NULL || *enviro == NULL)
	{
		free(g_shell);
		ft_exit("No environment specified.", 0, 1, EXIT_FAILURE);
	}
	else
		init_env(enviro);
	return (g_shell);
}

static void			init_editor(void)
{
	struct winsize	w;
	int				ret;

	if ((g_editor = malloc(sizeof(t_editor))) == NULL)
		ft_exit(INTERN_ERR, 0, 0, EXIT_FAILURE);
	prompt_reset();
	if ((ret = open("/dev/tty", O_WRONLY)) < 0)
		ft_exit("Error opening the /dev/tty", 1, 1, EXIT_FAILURE);
	g_editor->tty_fd = ret;
	if ((ioctl(g_editor->tty_fd, TIOCGWINSZ, &w)) < 0)
		ft_exit("ioctl", 0, 1, EXIT_FAILURE);
	ft_bzero(g_editor->cmd, ARG_MAX);
	ft_bzero(g_editor->cpy_buff, ARG_MAX);
	g_editor->win_height = w.ws_row;
	g_editor->win_width = w.ws_col;
	command_reset();
	g_editor->quotes = 0;
	g_editor->open_subsh = 0;
	g_editor->term = NULL;
	g_editor->oldterm = NULL;
	g_editor->flag_sigint = 0;
}

int					main(int argc, char **argv, char **enviro)
{
	char	*str;

	(void)argv;
	(void)argc;
	init_editor();
	g_shell = init_shell(enviro);
	init_term();
	init_signal_handlers();
	if (!isatty(STDIN_FILENO))
	{
		while (get_next_line(STDIN_FILENO, &str) != 0)
		{
			parser(ft_strdup(str));
			free(str);
		}
		restore_default_conf();
		return (0);
	}
	while (1)
	{
		prompt_display();
		detect_input();
	}
	return (0);
}
