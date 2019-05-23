/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:09:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/23 10:57:00 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "sh_error.h"
#include "ast.h"

/*
** This is the file where  we build a list of tokens by calling next_token.
** The last token always have to be of type TYPE_END.
** Each new token have to be check by the previous token
** to see if the new token is enable by grammar.
*/

static int	ambigous_redirect(t_ast *token)
{
	while (token->next)
	{
		if (token->next->level_prior == level_4)
		{
			if (token->type != WORD_TOK || (token->prev && token->prev->type == WORD_TOK))
			{
				ft_dprintf(STDERR_FILENO, AMBI_REDIR);
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}

int				parser(char *line)
{
	t_ast	*token_head;
	t_ast	*tmp;
	t_ast	*ast_root;
	int		ret;

	token_head = NULL;
	ast_root = NULL;
	ret = 0;
	if (loop_tok(&token_head, &line))
		ret = 1;
	else if (token_head->next)
	{
		if (!(tmp = look_arg(token_head))
				|| expansion_tok(token_head)
				|| ambigous_redirect(token_head)
				|| create_arg(token_head)
				|| create_ast(&ast_root, token_head))
			ret = 1;
		else
		{
			ret = run_ast(ast_root, token_head);
		}
	}
	del_ast(&token_head);
	return (ret);
}
