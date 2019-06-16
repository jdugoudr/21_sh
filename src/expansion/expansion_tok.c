/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:48:54 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 18:06:39 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	init_convert(char ***tmp, char **str, t_ast **new)
{
	char	*new_str;
	int		count;

	count = 0;
	if ((new_str = env_subst(ft_strdup(*str))) == NULL)
		return (-1);
	if ((*tmp = ft_strsplit_ws(new_str)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		free(new_str);
		ft_strdel(str);
		return (-1);
	}
	if ((*tmp)[0] == NULL)
		*new = NULL;
	else if ((*new = create_tok_el((*tmp)[0], NULL, NULL)) == NULL)
	{
		ft_tabstrdel(tmp, 0);
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (-1);
	}
	else
		count = 1;
	free(new_str);
	return (count);
}

/*
 ** We create and fill all other token if they are
 ** more than one word in the variable => $VAR="ls -l"
*/

static int	convert_var(char *str, int *count, t_ast **new)
{
	char	**tmp;
	int		i;

	i = 1;
	tmp = NULL;
	if ((*count = init_convert(&tmp, &str, new)) == -1)
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

static void	new_token(t_ast **el, int count, t_ast *tmp_del, t_ast *new)
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

static int	check_var(t_ast **el, int count, t_ast **end)
{
	t_ast	*new;
	t_ast	*tmp_del;

	tmp_del = (*el)->next;
	if ((convert_var((*el)->next->value, &count, &new)))
		return (1);
	if (tmp_del->type == WORD_TOK)
	{
		new_token(el, count, tmp_del, new);
		if (tmp_del == *end)
			*end = *el;
		del_token(&(tmp_del));
	}
	return (0);
}

int			expansion_tok(t_ast *el, t_ast **end)
{
	while (el->next && el->next != (*end)->next)
	{
		if (el->next->type & WORD_TOK && (!el->next->next
			|| (el->next->next && (el->next->next->type & DLESS_TOK) == 0)))
		{
			if (ft_strchr(el->next->value, '$'))
			{
				if (check_var(&el, 0, end))
					return (1);
			}
			else
			{
				if (el->next->value[0] == '~' && (el->next->value[1] == '/'
						|| el->next->value[1] == '\0'))
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
