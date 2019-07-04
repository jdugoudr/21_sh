/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 16:52:49 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 18:17:21 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast.h"
#include "check_next.h"
#include "exec_cmd.h"
#include "libft.h"
#include "sh_error.h"

static void	set_quot(t_ast *tok, char c)
{
	if (c == '"')
		tok->type = DQUOT_TOK;
	else
		tok->type = QUOT_TOK;
	tok->f_tok_next = &check_for_word;
	tok->f_exec = &exec_word;
}

t_ast		*quot_find(char **line, t_ast *tok, char c)
{
	int	i;

	i = 1;
	while ((*line)[i] != c && (*line)[i] != '\0')
		i++;
	tok->level_prior = level_6;
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
		set_quot(tok, c);
		(*line) += i + 1;
	}
	return (tok);
}
