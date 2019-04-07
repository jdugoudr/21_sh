/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:08:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/06 19:03:17 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "sh_error.h"

/*
** Here we execute word.
** We have to fork if word is a comand,
** not if it's a built-ins.
*/

int	exec_word(t_ast *el)
{
	pid_t	child;
	int		r;

	r = 0;
	child = fork();
	if (child == 0)
	{
		execve(el->arg_cmd[0], el->arg_cmd, NULL);
	}
	else if (child == -1)
	{
		ft_fprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	else
	{
		waitpid(child, &r, 0);
	}
	return (r);
}
