/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:59:49 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/25 17:10:10 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token_define.h"
#include "check_next.h"
#include "libft.h"
#include "sh_error.h"

t_ast	*and_find(char **line, t_ast *tok/*, bool *is_cmd*/)
{
	if ((*line)[1] == '&'/* && *is_cmd == 0*/)
	{
		tok->type = AND_IF;
		tok->value = NULL;
		tok->f_tok_next = &check_for_and_or;
		(*line) += 2;
//		*is_cmd = 1;
	}
	else
	{
		ft_fprintf(STDERR_FILENO, UNEX_SYMB, (*line)[0]);
		free(tok);
		tok = NULL;
	}
	return (tok);
}
