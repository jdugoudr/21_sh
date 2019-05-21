/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:35:46 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/21 17:04:05 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast.h"
#include "libft.h"
#include "sh_error.h"

/*
** This is the file where new tokens are create.
** If the current character is uncote space or tab,
** we just consume it. Otherwise, we try to find out
** wich token type it is.
*/

static t_ast	*still_find(char **line, t_ast *new_tok, bool *is_name)
{
	if (**line == ')')
	{
		del_token(&new_tok);
		ft_dprintf(STDERR_FILENO, UNEX_SYMB, **line);
		return (NULL);
	}
	else if (**line == '\0')
	{
		new_tok->type = TYPE_END;
		new_tok->value = NULL;
		new_tok->level_prior = level_7;
		return (new_tok);
	}
	else
		return (word_find(line, new_tok, is_name));
}

static t_ast	*find_token(char **line, t_ast *new_tok, bool *is_name)
{
	if (**line == '&')
		return (and_find(line, new_tok));
	else if (**line == '|')
		return (or_find(line, new_tok));
	else if (**line == '\'' || **line == '\"')
		return (quot_find(line, new_tok, **line));
	else if (**line == ';')
		return (semi_find(line, new_tok));
	else if (**line == '<')
		return (less_find(line, new_tok, NULL));
	else if (**line == '>')
		return (great_find(line, new_tok, NULL));
	else if (**line == '(')
		return (sub_find(line, new_tok));
	else
		return (still_find(line, new_tok, is_name));
}

t_ast			*next_token(char **line, bool *is_name)
{
	t_ast	*new_tok;

	if ((new_tok = create_token()) == NULL)
		return (NULL);
	consume(line);
	return (find_token(line, new_tok, is_name));
}
