/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:53:54 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/10 15:15:33 by jdugoudr         ###   ########.fr       */
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

static t_ast	*skip_el(t_ast *start)
{
	while (start && start->type != WORD_TOK)
		start = start->next;
	return (start);
}

static int		count_arg(t_ast *start, t_ast **end)
{
	t_ast	*el;
	int		count;

	count = 1;
	if (!start || start->type != WORD_TOK)
		return (0);
	el = start;
	while (el->next && el->next->type == WORD_TOK)
	{
		count++;
		el = el->next;
	}
	*end = el;
	return (count);
}

static t_ast	*del_arg(t_ast *el)
{
	t_ast	*tmp;

	tmp = el->prev;
	el->prev->next = el->next;
	el->next->prev = el->prev;
	del_token(&el);
	return (tmp);
}

static int		add_arg(t_ast *el, char **lst_arg, int count)
{
	char	*el_arg;
	t_ast	*el_next;

	if (!el || el->type != WORD_TOK)
		return (0);
	el_next = el->prev;
	if ((el_arg = ft_strdup(el->value)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	lst_arg[count] = el_arg;
	lst_arg[count + 1] = NULL;
	if (count)
		del_arg(el);
	else if (count == 0)
		el->arg_cmd = lst_arg;
	count++;
	return (add_arg(el_next, lst_arg, count));
}

int				create_arg(t_ast *start)
{
	char	**lst_arg;
	t_ast	*end;
	t_ast	*el;
	int		count;

	el = start;
	while (el)
	{
		if ((el = skip_el(el)) == NULL)
			break ;
		count = count_arg(el, &end);
		if (count)
		{
			if ((lst_arg = malloc((count + 1) * sizeof(char *))) == NULL)
				return (1);
			lst_arg[0] = NULL;
			if (add_arg(end, lst_arg, 0))
				return (1);// verifier si pas de leaks !!!
		}
		el = end->next;
	}
	return (0);
}
