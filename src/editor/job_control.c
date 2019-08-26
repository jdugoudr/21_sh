/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 01:36:35 by mdaoud            #+#    #+#             */
/*   Updated: 2019/08/26 02:51:22 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "sh_error.h"
#include "editor.h"
#include "ast.h"
#include "libft.h"
#include "shell21.h"
#include "job_control.h"
#include "parser.h"
#include <sys/types.h>
// #include <types.h>
#include <unistd.h>

static int			execve_cmd(char **cmd)
{
	int	child;
	int	ret;

	// (void)ret;
	child = fork();
	if (child == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		ret = -1;
		return (1);
	}
	else if (child == 0)
	{
		execve(cmd[0],cmd, g_shell->env);
		// reset_term(head, ret);
		ret = 0;
	}
	else
		waitpid(-1, &ret, 0);
	return (ret);
}
static void			process_cmd(char	*cmd)
{
	char	**com_cmd;
	char	**path_tab;
	char	*temp;
	int		i;

	com_cmd = ft_strsplit(cmd, ' ');
	if (com_cmd[0][0] == '/')
	{
		if (access(com_cmd[0], F_OK) == 0)
		{
			execve_cmd(com_cmd);
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "%s does not exist\n", cmd);
		}
		return ;
	}
	temp = get_env_value("PATH");
	path_tab = ft_strsplit(temp, ':');
	i = 0;
	while (path_tab[i] != NULL)
	{
		temp = ft_strjoin(path_tab[i], "/", 0);
		temp = ft_strjoin(temp, com_cmd[0], 1);
		// ft_printf("Trying : %s\n", temp);
		if (access(temp, F_OK) == 0)
		{
			// ft_printf("FOUND IT\n");
			free(com_cmd[0]);
			com_cmd[0] = temp;
			execve_cmd(com_cmd);
			return ;
		}
		free(temp);
		i++;
	}
	ft_dprintf(STDERR_FILENO, "Coudnlt not find any good path\n");
}

void			job_control(char	*cmd)
{
	(void)cmd;
	ft_printf("shell pid: %d, shell ppid: %d, shell pgid: %d\n", getpid(), getppid(), getpgid(g_shell->pgid));
	// parser(ft_strdup(cmd));
	g_shell->pgid = getpid ();
	if (setpgid(g_shell->pgid, g_shell->pgid))
	{
		ft_dprintf(STDERR_FILENO, "setgpid error\n");
		return ;
	}
	ft_printf("shell pid: %d, shell ppid: %d, shell pgid: %d\n\n", getpid(), getppid(), getpgid(g_shell->pgid));
	tcsetpgrp (g_editor->tty_fd, g_shell->pgid);
	process_cmd(cmd);
}
