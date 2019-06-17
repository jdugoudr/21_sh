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
#include "parser.h"
#include "ast.h"
#include "sh_error.h"
#include "libft.h"

/*
** Create a array of string and del all word token which are argument
*/

static int		count_arg(t_ast *start)
{
	t_ast	*el;
	int		count;

	count = 1;
	if (!start || start->level_prior != LEVEL_MIN)
		return (0);
	el = start;
	while (el->prev && el->prev->level_prior == LEVEL_MIN)
	{
		count++;
		el = el->prev;
	}
	return (count);
}

static int		add_arg(t_ast *el, char **lst_arg, int count, int nb_arg)
{
	char	*el_arg;

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

int				create_arg(t_ast *start)
{
	char	**lst_arg;
	t_ast	*el;
	int		count;

	el = start;
	count = count_arg(el);
	if (count)
	{
		if ((lst_arg = malloc((count + 1) * sizeof(char *))) == NULL)
			return (1);
		lst_arg[0] = NULL;
		if (add_arg(el, lst_arg, 0, count))
		{
			ft_tabstrdel(&lst_arg, 0);
			return (1);
		}
		el->arg_cmd = lst_arg;
	}
	return (0);
}
