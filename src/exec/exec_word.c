/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:08:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/14 16:24:42 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "sh_error.h"
#include "ast.h"

//#include <sys/types.h>//linux
//#include <sys/wait.h>//linux

/*
** Here we execute word.
** We have to fork if word is a comand,
** not if it's a built-ins.
*/

static void	init_built(t_built *built_tab)
{
	built_tab[0].name = "echo";
	built_tab[0].func = NULL;
	built_tab[1].name = "cd";
	built_tab[1].func = NULL;
	built_tab[2].name = "setenv";
	built_tab[2].func = NULL;
	built_tab[3].name = "unsetenv";
	built_tab[3].func = NULL;
	built_tab[4].name = "env";
	built_tab[4].func = NULL;
}

static void	free_exit(int r, t_ast *head)
{
	free_shell();
	free_editor();
	del_ast(&head);
	exit(r);
}

static void	free_reset_fd(int ***save_fd, t_ast *head)
{
	int i;
	int r;

	i = 0;
	r = 0;
	while (*save_fd && (*save_fd)[i])
	{
		if (dup2((*save_fd)[i][1], (*save_fd)[i][0]) == -1)
		{
			r = 1;
			ft_dprintf(STDERR_FILENO, INTERN_ERR);
		}
		close((*save_fd)[i][1]);
		i++;
	}
	del_saved_fd(save_fd);
	if (r)
		free_exit(r, head);
}

static int 	loop_redirect(t_ast *el, t_ast *head, t_ast *cmd, t_built *builtin, int ***save_fd)
{
	int	fd;
	int	r;

	fd = 0;
	r = 0;
	if (el->father && el->father->level_prior == level_4)
	{
		if ((fd = find_and_exec_redirect(el->father, save_fd)) == -1)
			return (1);
		r = loop_redirect(el->father, head, cmd, builtin, save_fd);
		if ((el->father->type & (LESS_FD_TOK | GREAT_FD_TOK | DGREAT_FD_TOK)) == 0)
			close(fd);
		return (r);
	}
	else if (builtin)
		ft_printf("exec builtin\n");
		//return (builtin.func(cmd->arg_cmd));
	else
		r = check_bin(cmd, head);
	free_reset_fd(save_fd, head);
	return (r);
}

static int 	fork_command(t_ast *el, t_ast *head, int ***save_fd)
{
	int 	child;
	int 	ret;

	child = fork();
	if (child == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	else if (child == 0)
	{
		ret = loop_redirect(el, head, el, NULL, save_fd);
		free_exit(ret, head);
	}
	else
		waitpid(child, &ret, 0);
	return (ret);
}

int	exec_word(t_ast *el, t_ast *head)
{
	t_built	built_tab[NB_BUILT];
	int		i;
	int		**save_fd;

	save_fd = NULL;
	init_built(built_tab);
	i = 0;
	while (i < NB_BUILT && ft_strcmp(el->value, built_tab[i].name) != 0)
		i++;
	if (i < NB_BUILT)
		return (loop_redirect(el, head, el, built_tab + i, &save_fd));
	else
		return (fork_command(el, head, &save_fd));//a suprimer
}
