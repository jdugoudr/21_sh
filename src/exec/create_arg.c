/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:53:54 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 18:30:26 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_define.h"
#include "exec_cmd.h"
#include "ast.h"
#include "sh_error.h"
#include "libft.h"

/*
** Create a array of string
*/

static int	add_arg(t_ast *el, char **lst_arg, int count, int nb_arg)
{
	char	*el_arg;

	while (count < nb_arg && el && el->level_prior <= LEVEL_REDI)
	{
		if (el->level_prior == LEVEL_MIN
			&& (!el->next || el->next->level_prior != LEVEL_REDI))
			break ;
		el = el->prev;
	}
	if (!el || count == nb_arg)
		return (0);
	if ((el_arg = ft_strdup(el->value)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	lst_arg[count] = el_arg;
	lst_arg[count + 1] = NULL;
	count++;
	return (add_arg(el->prev, lst_arg, count, nb_arg));
}

int			create_arg(t_cmd w_ast, int nb_arg)
{
	char	**lst_arg;

	if (nb_arg == 0)
		return (0);
	if ((lst_arg = malloc((nb_arg + 1) * sizeof(char *))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	lst_arg[0] = NULL;
	if (add_arg(w_ast.start, lst_arg, 0, nb_arg))
	{
		ft_tabstrdel(&lst_arg, 0);
		return (1);
	}
	w_ast.cmd->arg_cmd = lst_arg;
	return (0);
}
