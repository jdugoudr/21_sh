/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:08:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/13 19:12:58 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "sh_error.h"
#include "shell21.h"
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

int	exec_word(t_ast *el, t_ast *head)
{
	t_built	built_tab[NB_BUILT];
	int		i;

	(void)head;
	init_built(built_tab);
	i = 0;
	while (i < NB_BUILT && ft_strcmp(el->value, built_tab[i].name) != 0)
		i++;
	if (i < NB_BUILT)
		return (built_tab[i].func(el->arg_cmd));
	else
		return (check_bin(el, head));
}
