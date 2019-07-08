/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 10:05:24 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 18:07:20 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "sh_error.h"
#include "check_next.h"
#include "ast.h"
#include "exec_cmd.h"

/*
** We take the all string between ( and ) and we create a new tree with just
** this part of the complete line command.
** Those tokens are in a defirrent tree but in the same list token. They will
** be free with the other
*/

static int		sub_parser(char *line, t_ast **token_head, t_ast **ast_root)
{
	int		ret;

	ret = 0;
	if (loop_tok(token_head, &line))
		ret = 1;
	else if ((*token_head)->next == NULL)
	{
		ft_dprintf(STDERR_FILENO, SYNTAX_ERR);
		ret = 1;
	}
	else if (create_ast(ast_root, *token_head))
		ret = 1;
	if (ret)
		del_ast(token_head);
	return (ret);
}

static t_ast	*fill_tok(t_ast *tok, char **line, int i)
{
	tok->type = SUB_SHELL;
	tok->f_tok_next = &check_for_sub;
	tok->f_exec = &exec_sub_shell;
	(*line) += i + 1;
	if (sub_parser(tok->value, &(tok->head_sub), &(tok->ast_sub)))
	{
		del_token(&tok);
		return (NULL);
	}
	return (tok);
}

t_ast			*sub_find(char **line, t_ast *tok)
{
	int	i;

	i = 1;
	while ((*line)[i] != ')' && (*line)[i])
		i++;
	if ((*line)[i] == '\0')
	{
		ft_dprintf(STDERR_FILENO, SYNTAX_ERR);
		del_token(&tok);
	}
	else if ((tok->value = ft_strndup((*line) + 1, i - 1)) == NULL)
	{
		del_token(&tok);
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
	}
	else
	{
		tok->level_prior = level_6;
		tok = fill_tok(tok, line, i);
	}
	return (tok);
}
