/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:09:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/17 14:25:48 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "sh_error.h"
#include "ast.h"
#include "exec_cmd.h"

/*
** This is the file where  we build a list of tokens by calling next_token.
** The last token always have to be of type TYPE_END.
** Each new token have to be check by the previous token
** to see if the new token is enable by grammar.
*/

static int	init_parser(char *line, t_ast **head, t_ast **root)
{
	*head = NULL;
	*root = NULL;
	if (line == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (0);
}

int			parser(char *line)
{
	t_ast		*token_head;
	t_ast		*ast_root;
	static int	ret = 0;
	char		*save_line;

	save_line = line;
	if (init_parser(line, &token_head, &ast_root)
		|| loop_tok(&token_head, &line))
		ret = 1;
	else if (token_head->next)
	{
		if (create_ast(&ast_root, token_head))
			ret = 1;
		else
			ret = run_ast(ast_root, token_head, ret);
	}
	free(save_line);
	del_ast(&token_head);
	return (ret);
}
