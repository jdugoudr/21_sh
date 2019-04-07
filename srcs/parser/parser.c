/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:09:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/07 10:56:49 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "sh_error.h"
#include "check_next.h"
#include "ast.h"
#include "run_ast.h"

/*
** This is the file where  we build a list of tokens by calling next_token.
** The last token always have to be of type TYPE_END.
** Each new token have to be check by the previous token
** to see if the new token is enable by grammar.
*/

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
	if ((*token_head))
		(*token_head)->prev = tok;
	*token_head = tok;
	return (0);
}

static int	loop_tok(t_ast **token_head, char **line)
{
	t_ast	*token;
	bool	is_name;

	is_name = 1;
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
		if ((*token_head)->type & L_IS_NAME)
			is_name = 0;
		else
			is_name = 1;
	}
	if (!token)
		return (1);
	return (0);
}

static t_ast	*look_redir(t_ast *start)
{
	t_ast	*el;

	el = start;
	if (start == NULL)
		return (NULL);
	while (el->next)
	{
		if (el->next->level_prior > level_4)
			break ;
		el = el->next;
	}
	start = sort_redirect(start, el->next);
	el->next = look_redir(el->next);
	return (start);
}

static t_ast	*look_arg(t_ast *start)
{
	t_ast	*el;

	el = start;
	if (start == NULL)
		return (NULL);
	while (el->next)
	{
		if (el->next->level_prior > level_4)
			break ;
		el = el->next;
	}
	if ((start = create_arg(start, el->next)))
		el->next = look_arg(el->next);
	return (start);
}

int			parser(char *line)
{
	t_ast	*token_head;
	t_ast	*tmp;
	t_ast	*ast_root;

	token_head = NULL;
	ast_root = NULL;
	if (loop_tok(&token_head, &line) || !(tmp = look_arg(token_head))
			||!(token_head = look_redir(tmp))
			|| create_ast(&ast_root, token_head))
	{
		del_ast(&token_head);
		return (1);
	}
	run_ast(ast_root);//////////////////a protoger
	del_ast(&token_head);
	return (0);
}
