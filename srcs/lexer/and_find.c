/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:59:49 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/26 13:04:47 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token_define.h"
#include "check_next.h"
#include "libft.h"
#include "sh_error.h"

t_ast	*and_find(char **line, t_ast *tok)
{
	if ((*line)[1] == '&')
	{
		tok->type = AND_IF;
		tok->value = NULL;
		tok->level_prior = level_2;
		tok->f_tok_next = &check_for_and_or;
		(*line) += 2;
	}
	else
	{
		ft_fprintf(STDERR_FILENO, UNEX_SYMB, (*line)[0]);
		free(tok);
		tok = NULL;
	}
	return (tok);
}
