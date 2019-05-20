/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:08:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/20 10:45:35 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "sh_error.h"
#include "ast.h"

#include "fcntl.h"

//#include <sys/types.h>//linux
//#include <sys/wait.h>//linux

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

static void	free_reset_fd(t_save_fd **fd_lst, t_ast *head)
{
	int 		r;
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
	{
		free_shell();
		free_editor();
		del_ast(&head);
		exit(r);
	}
}

static int 	loop_redirect(t_ast *el, t_ast *head, t_ast *cmd, t_built *builtin, t_save_fd **fd_lst)
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
		return (loop_redirect(el->father, head, cmd, builtin, fd_lst));
	}
	else if (builtin)
		write(1, "execution de built\n", 19);
	else
		r = check_bin(cmd, head);
	free_reset_fd(fd_lst, head);
	return (r);
}

static int 	fork_command(t_ast *el, t_ast *head, t_save_fd **save_fd)
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
		free_shell();
		free_editor();
		del_ast(&head);
		exit(ret);
	}
	else
		waitpid(child, &ret, 0);
	return (ret);
}

int	exec_word(t_ast *el, t_ast *head)
{
	t_built		built_tab[NB_BUILT];
	int			i;
	t_save_fd	*save_fd;

	save_fd = NULL;
	init_built(built_tab);
	i = 0;
	while (i < NB_BUILT && ft_strcmp(el->value, built_tab[i].name) != 0)
		i++;
	if (i < NB_BUILT)
		return (loop_redirect(el, head, el, built_tab + i, &save_fd));
	else
		return (fork_command(el, head, &save_fd));
}
