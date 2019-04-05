/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 10:05:24 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/05 11:20:01 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "del_ast.h"
#include "check_next.h"
#include "libft.h"
#include "sh_error.h"
#include "exec_cmd.h"

t_ast	*sub_find(char **line, t_ast *tok)
{
	int	i;

	i = 1;
	while ((*line)[i] != ')' && (*line)[i])
		i++;
	if ((*line)[i] == '\0')
	{
		ft_fprintf(STDERR_FILENO, SYNTAX_ERR);
		del_token(&tok);
	}
	else if ((tok->value = ft_strndup((*line) + 1, i - 1)) == NULL)
	{
		del_token(&tok);
		ft_fprintf(STDERR_FILENO, INTERN_ERR);
	}
	else
	{
		tok->type = SUB_SHELL;
		tok->f_tok_next = &check_for_sub;
		tok->f_exec = &exec_sub_shell;
		(*line) += i + 1;
	}
	tok->level_prior = level_6;
	return (tok);
}
