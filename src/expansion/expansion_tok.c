/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:48:54 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/21 12:49:00 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_define.h"
#include "ast.h"
#include "sh_error.h"
#include "libft.h"

/*
** For each word token, we look if a varible is present.
** If yes we replace it and check if the new string contains whitespace.
** If yes we split the the string and tokens in the list.
*/

static int	init_convert(char ***tmp, char **str, int *count, t_ast **new)
{
	char	*new_str;

	*count = 0;
	if ((new_str = env_subst(ft_strdup(*str))) == NULL)
		return (1);
	if ((*tmp = split_whitespaces(new_str)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		free(new_str);
		ft_strdel(str);
		return (1);
	}
	if ((*tmp)[0] == NULL)
		*new = NULL;
	else if ((*new = create_tok_el((*tmp)[0], NULL, NULL)) == NULL)
	{
		ft_tabstrdel(tmp, 0);
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	else
		*count = 1;
	free(new_str);
	return (0);
}

static int	convert_var(char *str, int *count, t_ast **new)
{
	char	**tmp;
	int		i;

	i = 1;
	tmp = NULL;
	if (init_convert(&tmp, &str, count, new))
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

static int	convert_tild(char **str)
{
	char	*tmp;
	char 	*value;

	if ((value = get_env_value("HOME")) == NULL)//get env value fait un dup !!!
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	tmp = *str;
	*str = ft_strjoin(value, *str + 1, 1);
	free(tmp);
	if (*str == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (0);
}

static int	check_var(t_ast **el)
{
	t_ast	*new;
	t_ast	*tmp_del;
	int		count;

	tmp_del = (*el)->next;
	if ((convert_var((*el)->next->value, &count, &new)))
		return (1);
	if (!new)//si la variable est vide ou n'existe pas ou saute le token concerne
	{
		if ((*el)->next->next)
			(*el)->next->next->prev = *el;
		(*el)->next = (*el)->next->next;
	}
	else//si il y a quelque chose
	{
		new->prev = (*el);
		(*el)->next = new;
		while (count-- > 1)//si la variable contenai plusieur mots on les a splité en plusieur tok on se place au dernier
			new = new->next;
		new->next = tmp_del->next;
		if (tmp_del->next)
			tmp_del->next->prev = new;
		(*el) = new;
	}
	del_token(&(tmp_del));
	return (0);
}

int			expansion_tok(t_ast *head)
{
	t_ast	*el;

	el = head;
	while (el->next)
	{
			if (el->next->type & WORD_TOK)
		{
			if (ft_strchr(el->next->value, '$'))
			{
				if (check_var(&el))
					return (1);
			 }
			else 
			{
				if (el->next->value[0] == '~' && (el->next->value[1] == '/' || el->next->value[1] == '\0'))
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
