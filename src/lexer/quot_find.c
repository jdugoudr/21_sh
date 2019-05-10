/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 16:52:49 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/10 15:05:07 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast.h"
#include "check_next.h"
#include "exec_cmd.h"
#include "libft.h"
#include "sh_error.h"

t_ast	*quot_find(char **line, t_ast *tok, char c)
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
		tok->type = WORD_TOK;
		tok->f_tok_next = &check_for_word;
		tok->f_exec = &exec_word;
		(*line) += i + 1;
	}
	return (tok);
}
