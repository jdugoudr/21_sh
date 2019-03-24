/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:07:38 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/24 17:51:48 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token_define.h"
#include "unistd.h"

t_ast	*or_find(char **line, t_ast *tok)
{
	if ((*line)[1] == '|')
	{
		tok->type = OR_IF;
		tok->value = NULL;
		(*line) += 2;
	}
	else
	{
		tok->type = PIPE_TOK;
		tok->value = NULL;
		(*line) += 1;
	}
	return (tok);
}
