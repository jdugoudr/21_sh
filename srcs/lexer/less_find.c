/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:27:52 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/05 11:18:13 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "check_next.h"
#include <stdlib.h>
#include "exec_cmd.h"

t_ast	*less_find(char **line, t_ast *tok, char *value)
{
	if ((*line)[1] == '<')
	{
		tok->type = DLESS_TOK;
		tok->value = value;
		tok->f_tok_next = &check_for_dless;
		tok->f_exec = &exec_dless;
		(*line) += 2;
	}
	else
	{
		tok->type = LESS_TOK;
		tok->value = value;
		tok->f_tok_next = &check_for_less;
		tok->f_exec = &exec_less;
		(*line) += 1;
	}
	tok->level_prior = level_4;
	return (tok);
}
