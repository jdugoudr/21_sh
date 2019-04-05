/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:53:54 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/05 09:32:03 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_define.h"
#include "parser.h"
#include "del_ast.h"
#include "sh_error.h"
#include "libft.h"

static int	count_arg(t_ast *start, t_ast *end)
{
	t_ast	*el;
	int		count;

	count = 0;
	el = start;
	while (el != end)
	{
		if (el->level_prior == LEVEL_REDI)
			el = el->next;
		else if (el->type == WORD_TOK)
			count++;
		el = el->next;
	}
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

static int	add_arg(t_ast *start, t_ast *end, char **tab_arg, int nb_word)
{
	int		i;
	t_ast	*el;

	i = 0;
	el = start;
	while (el != end)
	{
		if (i < nb_word && el->type == WORD_TOK
				&& (!(el->next) || el->next->level_prior != LEVEL_REDI))
		{
			i++;
			if ((tab_arg[nb_word - i] = ft_strdup(el->value)) == NULL)
			{
				ft_tabstrdel(&tab_arg, i);
				return (1);
			}
			if (i == nb_word)
			{
				el->arg_cmd = tab_arg;
			}
			else
				el = del_arg(el);
		}
		el = el->next;
	}
	tab_arg[i] = NULL;
	return (0);
}

t_ast		*create_arg(t_ast *start, t_ast *end)
{
	int		nb_word;
	char	**tab_arg;

	nb_word = count_arg(start, end);
	if (nb_word)
	{
		if ((tab_arg = malloc((nb_word + 1) * sizeof(char*))) == NULL)
		{
			ft_fprintf(STDERR_FILENO, INTERN_ERR);
			return (NULL);
		}
		tab_arg[0] = NULL;
		if (add_arg(start, end, tab_arg, nb_word))
		{
			del_ast(&start);
			return (NULL);
		}
	}
	return (start);
}
