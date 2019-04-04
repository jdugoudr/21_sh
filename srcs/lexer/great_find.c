/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   great_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:34:07 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/04 10:17:11 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "check_next.h"
#include <stdlib.h>

t_ast	*great_find(char **line, t_ast *tok, char *value)
{
	if ((*line)[1] == '>')
	{
		tok->type = DGREAT_TOK;
		tok->value = value;
		tok->f_tok_next = &check_for_dgreat;
		(*line) += 2;
	}
	else
	{
		tok->type = GREAT_TOK;
		tok->value = value;
		tok->f_tok_next = &check_for_great;
		(*line) += 1;
	}
	tok->level_prior = level_4;
	return (tok);
}
