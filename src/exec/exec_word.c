/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:08:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 12:58:05 by jdugoudr         ###   ########.fr       */
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
** and redirection.
**
** If the command is a not a builtin, we fork before applying redirection.
**
** After the execution of the command we need unset redirection.
** Every cahnged file descriptor are stock in a int array.
**
** save_fd[i][0] : executive fd
** save_fd[i][1] : saved of the old executive fd
**
** We have to dup saved fd in the executive fd and then close the save fd.
*/

static void	init_built(t_built *built_tab)
{
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
}

static void	free_reset_fd(t_save_fd **fd_lst, t_ast *head)
{
	int			r;
	t_save_fd	*lst;

	r = 0;
	lst = *fd_lst;
	while (lst)
	{
		if (lst->save_fd >= 0)
		{
			if (dup2(lst->save_fd, lst->old_fd) == -1)
			{
				r = 1;
				ft_dprintf(STDERR_FILENO, INTERN_ERR);
				break ;
			}
			close(lst->save_fd);
		}
		else
			close(lst->old_fd);
		lst = lst->next;
	}
	del_saved_fd(fd_lst);
	if (r)
		reset_term(head, 1);
}

static int	loop_redirect(t_ast *el, t_ast *head, t_built *blt, t_save_fd **fd_lst)
{
	int	r;

	r = 0;
	if (el->father && el->father->level_prior == level_4)
	{
		if (find_and_exec_redirect(el->father, fd_lst))
		{
			free_reset_fd(fd_lst, head);
			return (1);
		}
		el = el->father;
		return (loop_redirect(el, head, blt, fd_lst));
	}
	else if (blt)
		r = blt->func(el->arg_cmd);
	else
		r = check_bin(el);
	free_reset_fd(fd_lst, head);
	return (r);
}

static int	fork_command(t_ast *el, t_ast *head, t_save_fd **save_fd)
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
		ret = loop_redirect(el, head, NULL, save_fd);
		reset_term(head, ret);
	}
	else
		waitpid(child, &ret, 0);
	return (ret);
}

int			exec_word(t_ast *el, t_ast *head)
{
	t_built		built_tab[NB_BUILT];
	int			i;
	t_save_fd	*save_fd;
	t_ast		*end;

	end = el;
	while (end && end->level_prior < level_3 && end->level_prior >= LEVEL_MIN)
		end = end->prev;
	save_fd = NULL;
	init_built(built_tab);
	i = 0;
	if (expansion_tok(end, &el) || create_arg(el))
		return 1;
	if (!el || el->type != WORD_TOK)
		return (0);
	while (i < NB_BUILT && ft_strcmp(el->value, built_tab[i].name) != 0)
		i++;
	if (i < NB_BUILT)
		return (loop_redirect(el, head, built_tab + i, &save_fd));
	else
		return (fork_command(el, head, &save_fd));
}
