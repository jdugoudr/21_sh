/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:09:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/08 19:10:20 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "sh_error.h"
#include "ast.h"

//#include "../print_ast.c"//////////////
/*
** This is the file where  we build a list of tokens by calling next_token.
** The last token always have to be of type TYPE_END.
** Each new token have to be check by the previous token
** to see if the new token is enable by grammar.
*/

int				parser(char *line, t_shell *shell)
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
				|| create_arg(token_head)
				|| !(token_head = look_redir(tmp))
				|| create_ast(&ast_root, token_head))
			ret = 1;
		else
		{
			run_ast(ast_root, shell, token_head);
		}
	}
	del_ast(&token_head);
	return (ret);
}
