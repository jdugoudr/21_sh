/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:35:46 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/25 18:29:33 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "sh_error.h"

/*
** This is the file where new tokens are create.
** If the current character is uncote space or tab,
** we just consume it. Otherwise, we try to find out
** wich token type it is.
*/

static t_ast	*find_token(char **line, t_ast *new_tok, bool *is_name)
{
	if (**line == '&')
		return (and_find(line, new_tok/*, is_cmd*/));
	else if (**line == '|')
		return (or_find(line, new_tok/*, is_cmd*/));
	else if (**line == '\'' || **line == '\"')
		return (quot_find(line, new_tok, **line));
	else if (**line == '\0')
	{
		new_tok->type = TYPE_END;
		new_tok->value = NULL;
		return (new_tok);
	}
	else
	{
			return (word_find(line, new_tok, is_name));
//		ft_fprintf(STDERR_FILENO, UNEX_SYMB, **line);
//		free(new_tok);
		return (NULL);
	}
}

t_ast			*next_token(char **line, bool *is_name)
{
	t_ast	*new_tok;

	if ((new_tok = malloc(sizeof(t_ast))) == NULL)
	{
		ft_fprintf(STDERR_FILENO, INTERN_ERR);
		return (NULL);
	}
	new_tok->arg_cmd = NULL;
	new_tok->next = NULL;
	new_tok->left = NULL;
	new_tok->right = NULL;
	new_tok->value = NULL;
	consume(line);
	return (find_token(line, new_tok, is_name));
}
