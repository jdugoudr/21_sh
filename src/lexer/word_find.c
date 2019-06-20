/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:10:04 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/20 15:07:41 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"
#include "lexer.h"
#include "ast.h"
#include "token_define.h"
#include "libft.h"
#include "sh_error.h"
#include "exec_cmd.h"

/*
** If a word doesn't start by a digit or a '=' and have a '=', it's a NAME
** If a word start by '=' and token before was a NAME, it's a ASSIGN
** If a word is make of digits caraters follow by '<' or '>' it's a redirect
** Otherwise it's WORD
*/

static int	is_it_name(char *line)
{
	int	i;

	i = 0;
	if (ft_isdigit(*line) || *line == '=')
		return (0);
	while (ft_isalnum(line[i]) || line[i] == '_')
		i++;
	if (line[i] == '=')
		return (i);
	return (0);
}

static int	is_it_redirect(char **line, t_ast **tok)
{
	int		i;
	char	*value;

	i = 0;
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] == '<' || (*line)[i] == '>')
	{
		if ((value = ft_strndup(*line, i)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, INTERN_ERR);
			del_token(tok);
			return (-1);
		}
		(*line) += i;
		if ((*line)[0] == '<')
			*tok = less_find(line, *tok, value);
		else
			*tok = great_find(line, *tok, value);
		return (1);
	}
	else
		return (0);
}

static int	is_it_assign(char *line, t_ast *tok, bool *is_name)
{
	int	i;

	i = 0;
	while (line[i] != ' ' && ft_strchr(RESERVED, line[i]) == NULL
		&& line[i] != '\0')
		i++;
	if (*is_name && *line == '=')
	{
		tok->type = ASSIGN_TOK;
		tok->level_prior = level_5;
		tok->f_tok_next = &check_for_assign;
		tok->f_exec = &exec_assign;
	}
	else
	{
		tok->type = WORD_TOK;
		tok->level_prior = level_6;
		tok->f_tok_next = &check_for_word;
		tok->f_exec = &exec_word;
	}
	return (i);
}

t_ast		*word_find(char **line, t_ast *tok, bool *is_name)
{
	int		i;

	i = 0;
	if ((*is_name) && (i = is_it_name(*line)))
	{
		tok->type = NAME_TOK;
		tok->level_prior = level_6;
		*is_name = 1;
		tok->f_tok_next = &check_for_name;
	}
	else if (is_it_redirect(line, &tok))
		return (tok);
	else
	{
		i = is_it_assign(*line, tok, is_name);
		*is_name = 0;
	}
	if ((tok->value = ft_strndup(*line, i)) == NULL)
	{
		del_token(&tok);
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
	}
	(*line) += i;
	return (tok);
}
