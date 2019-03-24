/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:59:49 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/24 16:59:00 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token_define.h"
#include "libft.h"

t_ast	*and_find(char **line, t_ast *tok)
{
	if ((*line)[1] == '&')
	{
		tok->type = AND_IF;
		tok->value = NULL;
		tok->f_tok_next = NULL;
		(*line) += 2;
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "Syntax error near : %c\n", (*line)[0]);
		free(tok);
		tok = NULL;
		(*line) += 1;
	}
	return (tok);
}
