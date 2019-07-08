/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:12:35 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/27 20:09:00 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "token_define.h"
#include "exec_cmd.h"
#include "sh_error.h"
#include "libft.h"

t_ast	*create_tok_el(char *str, t_ast *prev, t_ast *next)
{
	t_ast	*el;
	char	*tmp;

	if ((el = create_token()) == NULL)
		return (NULL);
	if ((tmp = ft_strdup(str)) == NULL)
	{
		free(el);
		return (NULL);
	}
	el->value = tmp;
	el->prev = prev;
	el->next = next;
	el->level_prior = LEVEL_MIN;
	el->type = WORD_TOK;
	el->arg_cmd = NULL;
	el->left = NULL;
	el->right = NULL;
	el->father = NULL;
	el->f_exec = exec_word;
	el->f_tok_next = NULL;
	return (el);
}

t_ast	*create_token(void)
{
	t_ast	*new_tok;

	if ((new_tok = malloc(sizeof(t_ast))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (NULL);
	}
	new_tok->arg_cmd = NULL;
	new_tok->next = NULL;
	new_tok->prev = NULL;
	new_tok->left = NULL;
	new_tok->right = NULL;
	new_tok->father = NULL;
	new_tok->head_sub = NULL;
	new_tok->ast_sub = NULL;
	new_tok->value = NULL;
	new_tok->f_exec = NULL;
	new_tok->f_tok_next = NULL;
	return (new_tok);
}
