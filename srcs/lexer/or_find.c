/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:07:38 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/26 10:30:55 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token_define.h"
#include "sh_error.h"
#include <unistd.h>
#include "check_next.h"

t_ast	*or_find(char **line, t_ast *tok)
{
	if ((*line)[1] == '|')
	{
		tok->type = OR_IF;
		tok->value = NULL;
		tok->f_tok_next = &check_for_and_or;
		(*line) += 2;
	}
	else
	{
		tok->type = PIPE_TOK;
		tok->value = NULL;
		tok->f_tok_next = &check_for_pipe;
		(*line) += 1;
	}
	return (tok);
}
