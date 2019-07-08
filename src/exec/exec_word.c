/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:08:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/17 12:19:11 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec_cmd.h"
#include "sh_error.h"
#include "fcntl.h"
#include "libft.h"
#include "ast.h"

/*
** Here we execute simple command.
** a simple command is one command with 0, 1 or more arguments
** and redirection and assignation.
**
** If the command exist and is a not a builtin,
** we fork before applying redirection.
**
** After the execution of the command we need unset redirection.
** Every changed file descriptor are stock in a list.
**
** save_fd->old_fd  : executive fd
** save_fd->save_fd : saved of the old executive fd
**
** We have to dup saved fd in the executive fd and then close the save fd.
*/

static void	init_blt(char *cmd, int (**f)(char **))
{
	t_blt	built_tab[NB_BUILT];
	int		i;

	i = 0;
	built_tab[0].name = "echo";
	built_tab[0].func = builtin_echo;
	built_tab[1].name = "cd";
	built_tab[1].func = builtin_cd;
	built_tab[2].name = "setenv";
	built_tab[2].func = builtin_setenv;
	built_tab[3].name = "unsetenv";
	built_tab[3].func = builtin_unsetenv;
	built_tab[4].name = "env";
	built_tab[4].func = builtin_env;
	built_tab[5].name = "history";
	built_tab[5].func = builtin_history;
	built_tab[6].name = "exit";
	built_tab[6].func = builtin_exit;
	while (i < NB_BUILT && ft_strcmp(cmd, built_tab[i].name) != 0)
		i += 1;
	if (i < NB_BUILT)
		*f = built_tab[i].func;
}

/*
** We apply redirection and reset them after the command execution.
** Fd redirect are saved in list with the old fd id and the save fd id.
** The save fd id could be -1. That's mean the old fd was close. So we have
** to close it again before to leave.
*/

static int	exec_cmd(t_ast *cmd, int (*blt)(char **))
{
	int	r;

	r = 0;
	if (blt)
		r = blt(cmd->arg_cmd);
	else if (cmd && cmd->level_prior == LEVEL_MIN)
		r = check_bin(cmd);
	return (r);
}

static int	lp_redir(t_cmd w_ast, t_ast *hd, int (*blt)(char **), t_fd **fd_lt)
{
	int	nb_arg;
	int	r;

	nb_arg = 0;
	r = 1;
	while (w_ast.el->level_prior <= LEVEL_REDI && w_ast.el->type != TYPE_END)
	{
		if (w_ast.el->level_prior == LEVEL_REDI)
		{
			if (find_and_exec_redirect(w_ast.el, fd_lt))
				return (free_reset_fd(fd_lt, hd, 1));
			w_ast.el = w_ast.el->prev->prev;
		}
		else if (w_ast.el->level_prior <= LEVEL_REDI)
		{
			if (w_ast.el->level_prior == LEVEL_MIN)
				nb_arg++;
			w_ast.el = w_ast.el->prev;
		}
	}
	if (!create_arg(w_ast, nb_arg))
		r = exec_cmd(w_ast.cmd, blt);
	return (free_reset_fd(fd_lt, hd, r));
}

/*
** If it's a not a built in we fork before
** to do redirection and before to check if
** the command exist in the path.
*/

static int	fork_command(t_cmd w_ast, t_ast *head, t_fd **save_fd)
{
	int	child;
	int	ret;

	child = fork();
	if (child == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	else if (child == 0)
	{
		ret = lp_redir(w_ast, head, NULL, save_fd);
		reset_term(head, ret);
	}
	else
		waitpid(child, &ret, 0);
	return (ret);
}

/*
** We first try to find the command which will be execute.
** This could be a builtin, a binary
** in the PATH, or not be present in command line.
** Then we fork if it's exist and it's not a builtin
** and we execute redirection.
** After that we create the list of argument
** and execute the command if it's exist.
*/

int			exec_word(t_ast *el, t_ast *head, int ret)
{
	t_cmd	w_ast;
	t_fd	*save_fd;
	int		(*func)(char **cmd);

	if (expansion_tok(el->prev, &(w_ast.start), ret))
		return (1);
	func = NULL;
	w_ast.cmd = w_ast.start;
	w_ast.el = w_ast.start;
	save_fd = NULL;
	while (w_ast.cmd->level_prior <= LEVEL_REDI && w_ast.cmd->type != TYPE_END)
	{
		if (w_ast.cmd->level_prior == LEVEL_MIN && (!(w_ast.cmd->next)
				|| w_ast.cmd->next->level_prior != LEVEL_REDI))
			break ;
		w_ast.cmd = w_ast.cmd->prev;
	}
	if (w_ast.cmd->level_prior > LEVEL_REDI || w_ast.cmd->type == TYPE_END)
		return (lp_redir(w_ast, head, NULL, &save_fd));
	init_blt(w_ast.cmd->value, &func);
	if (func)
		return (lp_redir(w_ast, head, func, &save_fd));
	else
		return (fork_command(w_ast, head, &save_fd));
}
