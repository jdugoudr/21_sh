/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:08:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/10 15:49:03 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "sh_error.h"
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
		ft_printf("on execute builtin %s\n", built_tab[i].name);////
//		return (built_tab[i].func(el->arg_cmd));
	else
		return (check_bin(el));
	return (0);//a suprimer
}
