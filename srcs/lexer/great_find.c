/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   great_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:34:07 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/07 14:31:28 by jdugoudr         ###   ########.fr       */
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
** cmd >& 2     ==> & is consume and 2 is took as a name file
** cmd >&2name  ==> & is consume and 2name is took as a name file
** cmd >&2      ==> &2 is take as redirect
** If a valid fd is find. We create a new token WORD_TOK with is value is &2.
** So we have to check during execution if the file to redirect is a file to
** open or fd.
*/

static int		is_valid(char **line)
{
	int	size;

	size = 1;
	if ((*line)[size] == '-')
		while ((*line)[size] != ' ' && (*line)[size] != '\0')
			size++;
	else
	{
		while (ft_isdigit((*line)[size]))
			size++;
		if ((*line)[size] == '-')
		{
			ft_fprintf(STDERR_FILENO, AMBI_REDIR, (*line) + 1);
			return (1);
		}
	}
	if ((*line)[size] == ' ' || (*line)[size] == '\0')
		return (size);
	(*line) += 1;
	return (0);
}

static t_ast	*aggreg_redirect(char **line, t_ast *tok)
{
	int		size;
	t_ast	*new_tok;

	new_tok = NULL;
	if (**line == '&' && (size = is_valid(line)))
	{
		if ((new_tok = create_token()) == NULL
			   || (new_tok->value = ft_strndup(*line, size)) == NULL)
		{
			ft_fprintf(STDERR_FILENO, INTERN_ERR);
			del_token(&new_tok);
			del_token(&tok);
			return (NULL);
		}
		new_tok->next = tok;
		tok->prev = new_tok;
		new_tok->type = WORD_TOK;
		new_tok->f_tok_next = &check_for_word;
		new_tok->f_exec = &exec_word;
		new_tok->level_prior = level_6;
		(*line) += size;
	}
	return (tok);
}

t_ast	*great_find(char **line, t_ast *tok, char *value)
{
	if ((*line)[1] == '>')
	{
		tok->type = DGREAT_TOK;
		tok->value = value;
		tok->f_tok_next = &check_for_dgreat;
		tok->f_exec = &exec_dgreat;
		(*line) += 2;
	}
	else
	{
		tok->type = GREAT_TOK;
		tok->value = value;
		tok->f_tok_next = &check_for_great;
		tok->f_exec = &exec_great;
		(*line) += 1;
	}
	tok->level_prior = level_4;
	return (aggreg_redirect(line, tok));
}
