/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:09:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 15:55:14 by jdugoudr         ###   ########.fr       */
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

static int	init_parser(char *line, t_ast **head, t_ast **root, int *r)
{
	*head = NULL;
	*root = NULL;
	*r = 0;
	if (line == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (0);
}

int			parser(char *line)
{
	t_ast	*token_head;
	t_ast	*tmp;
	t_ast	*ast_root;
	int		ret;
	char	*save_line;

	save_line = line;
	if (init_parser(line, &token_head, &ast_root, &ret)
		|| loop_tok(&token_head, &line))
		ret = 1;
	else if (token_head->next)
	{
		if (!(tmp = look_arg(token_head)) || create_ast(&ast_root, token_head))
			ret = 1;
		else
			ret = run_ast(ast_root, token_head);
	}
	free(save_line);
	del_ast(&token_head);
	return (ret);
}
