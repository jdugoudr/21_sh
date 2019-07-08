/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 09:47:51 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/07/07 14:12:05 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "sh_error.h"
#include "lexer.h"
#include "ast.h"
#include "libft.h"

/*
** Check if the current token is avaible by using check_next() of the actual
** token_head
** If token_head is null (first token), token can only be a name, word,
** or sub_shell
*/

static int		check_token(t_ast **token_head, t_ast *tok, char **line)
{
	int	r;

	r = 0;
	if (*token_head == NULL && (tok->type & ENA_FIRST) == 0)
	{
		ft_dprintf(STDERR_FILENO, SYNTAX_ERR);
		r = 1;
	}
	else if (*token_head)
	{
		r = (*token_head)->f_tok_next(tok, line);
		if (r > 0 && ((*token_head)->type & DLESS_TOK) == 0)
			ft_dprintf(STDERR_FILENO, SYNTAX_ERR);
	}
	if (r)
	{
		del_token(&tok);
		return (1);
	}
	tok->next = *token_head;
	if ((*token_head))
		(*token_head)->prev = tok;
	*token_head = tok;
	return (0);
}

/*
** We take and check the next token.
** We have to check if the new token next already point on new token
** because redirect can create two token. Redirect token and WORD_TOKEN if
** this kind of command are given  :  cmd >&2
*/

int				loop_tok(t_ast **token_head, char **line)
{
	t_ast	*token;
	bool	is_name;

	is_name = 1;
	while ((token = next_token(line, &is_name)))
	{
		if (check_token(token_head, token, line))
			return (1);
		if ((*token_head)->type == TYPE_END)
			break ;
		if ((*token_head)->type & L_IS_NAME)
			is_name = 0;
		else
			is_name = 1;
	}
	if (!token)
		return (1);
	return (0);
}
