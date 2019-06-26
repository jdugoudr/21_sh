/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:48:54 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/20 15:20:49 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "token_define.h"
#include "ast.h"
#include "sh_error.h"
#include "libft.h"

/*
** For each word token, we look if a varible is present.
** If yes we replace it.
** If the word is not a quot word :
** We check if the new string contains whitespace.
** If yes we split the the string and add tokens in the list.
** If it's a quot word we just replace the value of the tokens by the new
** string.
*/

/*
** We take the new string.
** Split on white space and create a new token with the first
** new string.
*/

static int	convert_var(char ***tmp, t_ast **new, t_ast *el, int ret)
{
	char	*new_str;
	int		r;

	r = 0;
	if ((new_str = env_subst(ft_strdup(el->value), ret)) == NULL)
		return (-1);
	if (el->type == DQUOT_TOK || (el->next && el->next->type == DLESS_TOK))
	{
		free(el->value);
		el->value = new_str;
		return (r);
	}
	if ((*tmp = ft_strsplit_ws(new_str)) != NULL && (*tmp)[0] == NULL)
		*new = NULL;
	else if (*tmp == NULL || !(*new = create_tok_el((*tmp)[0], NULL, NULL)))
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		ft_tabstrdel(tmp, 0);
		r = -1;
	}
	else
		r = 1;
	free(new_str);
	return (r);
}

/*
** We create and fill all other token if they are
** more than one word in the variable => $VAR="ls -l"
*/

static int	fill_var(int *count, t_ast **new, t_ast *el, int ret)
{
	char	**tmp;
	int		i;

	i = 1;
	tmp = NULL;
	if ((*count = convert_var(&tmp, new, el, ret)) == -1)
		return (1);
	else if (*count)
	{
		while (tmp[i])
		{
			if (((*new)->prev = create_tok_el(tmp[i], NULL, *new)) == NULL)
			{
				ft_tabstrdel(&tmp, 0);
				del_ast(new);
				ft_dprintf(STDERR_FILENO, INTERN_ERR);
				return (1);
			}
			(*new) = (*new)->prev;
			i++;
			(*count)++;
		}
	}
	ft_tabstrdel(&tmp, 0);
	return (0);
}

/*
** If it's non quot word
** We re-build connexion with new token
*/

static void	cp_link(t_ast **el, int count, t_ast *tmp_del, t_ast *new)
{
	if (!new)
	{
		if ((*el)->next->next)
			(*el)->next->next->prev = *el;
		(*el)->next = (*el)->next->next;
	}
	else
	{
		new->prev = (*el);
		(*el)->next = new;
		while (count-- > 1)
			new = new->next;
		new->next = tmp_del->next;
		if (tmp_del->next)
			tmp_del->next->prev = new;
		new->father = tmp_del->father;
		if (tmp_del->father)
		{
			if (tmp_del->father->right == tmp_del)
				tmp_del->father->right = new;
			else
				tmp_del->father->left = new;
		}
		(*el) = new;
	}
}

static int	check_var(t_ast **el, int count, t_ast **end, int ret)
{
	t_ast	*new;
	t_ast	*tmp_del;

	tmp_del = (*el)->next;
	if ((fill_var(&count, &new, (*el)->next, ret)))
		return (1);
	if (tmp_del->type == WORD_TOK
		&& (!tmp_del->next || tmp_del->next->type != DLESS_TOK))
	{
		cp_link(el, count, tmp_del, new);
		if (tmp_del == *end)
			*end = *el;
		del_token(&(tmp_del));
	}
	return (0);
}

int			expansion_tok(t_ast *el, t_ast **end, int ret)
{
	while (el->next && el->next != (*end)->next)
	{
		if (el->next->level_prior == LEVEL_MIN && el->next->type != QUOT_TOK)
		{
			if (ft_strchr(el->next->value, '$'))
			{
				if (check_var(&el, 0, end, ret))
					return (1);
			}
			else
			{
				if (el->next->value[0] == '~'
					&& !ft_isalnum(el->next->value[1]))
					if (convert_tild(&(el->next->value)))
						return (1);
				el = el->next;
			}
		}
		else
			el = el->next;
	}
	return (0);
}
