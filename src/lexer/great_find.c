/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   great_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:34:07 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/28 10:32:26 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "check_next.h"
#include "sh_error.h"
#include "ast.h"
#include <stdlib.h>
#include "exec_cmd.h"

/*
** Here we create the token redirect
** If imediatly after then token redirect the carachetere & is find
** we look for a valid file descriptor as follow :
** cmd >& 2     ==> & is consume and 2 is took as a file name
** cmd >&2name  ==> & is consume and 2name is took as a file name
** cmd >&2      ==> &2 is take as redirect
** If a valid fd is find. We create a new token WORD_TOK with is value is &2.
** So we have to check during execution if the file to redirect is a file to
** open or fd.
*/

static t_ast	*dgreat_find(char **line, t_ast *tok, char *value)
{
	(*line) += 1;
	if ((*line)[1] == '&')
	{
		tok->type = DGREAT_FD_TOK;
		tok->value = value;
		tok->f_tok_next = &check_for_redir_fd;
		tok->f_exec = &exec_word;
		(*line) += 1;
	}
	else
	{
		tok->type = DGREAT_TOK;
		tok->value = value;
		tok->f_tok_next = &check_for_dgreat;
		tok->f_exec = &exec_word;
	}
	(*line) += 1;
	return (tok);
}

t_ast			*great_find(char **line, t_ast *tok, char *value)
{
	if ((*line)[1] == '>')
		tok = dgreat_find(line, tok, value);
	else
	{
		if ((*line)[1] == '&')
		{
			tok->type = GREAT_FD_TOK;
			tok->value = value;
			tok->f_tok_next = &check_for_redir_fd;
			tok->f_exec = &exec_word;
			(*line) += 1;
		}
		else
		{
			tok->type = GREAT_TOK;
			tok->value = value;
			tok->f_tok_next = &check_for_great;
			tok->f_exec = &exec_word;
		}
		(*line) += 1;
	}
	tok->level_prior = level_4;
	return (tok);
}
