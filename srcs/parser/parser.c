/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:09:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/26 10:25:37 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "del_ast.h"
#include "lexer.h"
#include "libft.h"
#include "sh_error.h"
#include "check_next.h"

/*
** This is the file where  we build a list of tokens by calling next_token.
** The last token always have to be of type TYPE_END.
** Each new token have to be check by the previous token
** to see if the new token is enable by grammar.
*/

///////// delete this function before merge master !!

void		print_token(t_ast *tok)
{
	t_ast *el;

	el = tok;
	while (el)
	{
		ft_printf("actuel token => %s\n", el->value);
		ft_printf("actuel type => %d\n", el->type);
		el = el->next;
	}
}

/*
** Check if the current token is avaible by using check_next() of the actual
** token_head
** If token_head is null (first token), token can only be a name, word,
** or sub_shell
*/

static int	check_token(t_ast **token_head, t_ast *tok)
{
	if (*token_head == NULL && (tok->type & ENA_FIRST) == 0)
		return (1);
	else if (*token_head && (*token_head)->f_tok_next(tok))
		return (1);
	tok->next = *token_head;
	*token_head = tok;
	return (0);
}

static int	loop_tok(t_ast **token_head, char **line)
{
	t_ast	*token;
	bool	is_name;

	is_name = 0;
	while ((token = next_token(line, &is_name)))
	{
		if (check_token(token_head, token))
		{
			ft_fprintf(STDERR_FILENO, SYNTAX_ERR);
			del_token(&token);
			return (1);
		}
		if ((*token_head)->type == TYPE_END)
			break ;
	}
	if (!token)
		return (1);
	return (0);
}

int			parser(char *line)
{
	t_ast	*token_head;

	token_head = NULL;
	if (loop_tok(&token_head, &line))
	{
		del_ast(&token_head);
		return (1);
	}
	else
		print_token(token_head);/////// this is for debug
	del_ast(&token_head);
	return (0);
}
