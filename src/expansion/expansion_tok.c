/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:48:54 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/07 11:07:46 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_define.h"
#include "ast.h"
#include "libft.h"

//#include "../print_ast.c"/////////////////

/*
** For each word token, we look if a varible is present.
** If yes we replace it and check if the new string contains whitespace.
** If yes we split the the string and add tokens in the list.
*/

static int		split_arg(char **str, t_ast **el, t_ast *old)
{
	int		i;
	char	*tmp;
	char	c;

	tmp = *str;
	i = 0;
	while (tmp[i] != ' ' && tmp[i] != '\t' && tmp[i] != '\0')
		i++;
	c = tmp[i];
	tmp[i] = '\0';
	if (i == 0)
	{
		*str = NULL;
		*el = NULL;
		return (0);
	}
	if ((*el = create_tok_el(tmp, old->prev, old->next)) == NULL)
		return (1);
	tmp[i] = c;
	while (tmp[i] == ' ' || tmp[i] == '\t')
		i++;
	*str = tmp + i;
	return (0);
}

static int	convert_var(char *str, t_ast *old, t_ast **new)
{
	char	*new_str;
	char	*tmp;
	t_ast	*arg;
	t_ast	*el;
	int		r;

	r = 0;
	if ((new_str = env_subst(ft_strdup(str))) == NULL)
		return (1);
	tmp = new_str;
	if (split_arg(&tmp, &arg, old) == 0)
	{
		el = arg;
		while (el && (r = split_arg(&tmp, &(el->next), old)) == 0)
		{
			if (!el->next)
				break ;
			el = el->next;
		}
	if (!r && el)
		el->next = old->next;
	}
	free(new_str);
	*new = arg;
	return (r);
}

static int	check_var(t_ast **el)
{
	t_ast	*new;
	int		r;

	r = 0;
	if (ft_strchr((*el)->value, '$'))
	{
		if ((convert_var((*el)->value, (*el), &new)))
			return (1);
		if (!new)
		{
			new = (*el)->next;
		}
		(*el)->prev->next = new;
		if ((*el)->next)
			(*el)->next->prev = new;
		del_token(el);
		*el = new;
	}
	return (r);
}

int			expansion_tok(t_ast *head)
{
	t_ast	*el;

	el = head->next;
	while (el)
	{
		if (el->type & WORD_TOK && el->prev->type != DLESS_TOK)
		{
			if (check_var(&el))
				return (1);
		}
		el = el->next;
	}
	return (0);
}
