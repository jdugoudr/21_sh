/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 16:52:49 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/26 13:06:25 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "del_ast.h"
#include "check_next.h"
#include "libft.h"
#include "sh_error.h"

t_ast	*quot_find(char **line, t_ast *tok, char c)
{
	int	i;

	i = 1;
	while ((*line)[i] != c && (*line)[i])
		i++;
	if ((*line)[i] == '\0')
	{
		ft_fprintf(STDERR_FILENO, SYNTAX_ERR);
		del_token(&tok);
	}
	else if ((tok->value = ft_strndup((*line) + 1, i - 1)) == NULL)
	{
		del_token(&tok);
		ft_fprintf(STDERR_FILENO, INTERN_ERR);
	}
	else
	{
		tok->type = QUOT_TOK;
		tok->f_tok_next = &check_for_quot;
		(*line) += i + 1;
	}
	tok->level_prior = level_6;
	return (tok);
}
