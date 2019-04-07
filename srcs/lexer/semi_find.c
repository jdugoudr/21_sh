/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:07:36 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/06 16:15:43 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_define.h"
#include "lexer.h"
#include "check_next.h"
#include "exec_cmd.h"
#include <stdlib.h>

t_ast	*semi_find(char **line, t_ast *tok)
{
	tok->type = SEMI_COL;
	tok->level_prior = level_1;
	tok->value = NULL;
	tok->f_tok_next = &check_for_semi;
	tok->f_exec = &exec_semi_col;
	(*line) += 1;
	return (tok);
}
