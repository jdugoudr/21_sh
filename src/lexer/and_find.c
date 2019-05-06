/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:59:49 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/08 15:30:15 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token_define.h"
#include "check_next.h"
#include "libft.h"
#include "sh_error.h"
#include "exec_cmd.h"

t_ast	*and_find(char **line, t_ast *tok)
{
	if ((*line)[1] == '&')
	{
		tok->type = AND_IF;
		tok->value = NULL;
		tok->level_prior = level_2;
		tok->f_tok_next = &check_for_and_or;
		tok->f_exec = &exec_and_if;
		(*line) += 2;
	}
	else
	{
		ft_dprintf(STDERR_FILENO, UNEX_SYMB, (*line)[0]);
		free(tok);
		tok = NULL;
	}
	return (tok);
}
