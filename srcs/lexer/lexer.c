/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:35:46 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/24 17:46:18 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "sh_error.h"

/*
** This is the file where new tokens are create.
** If the current character is uncote space or tab,
** we just consume it. Otherwise, we try to find out
** wich token type it is.
*/

static t_ast	*find_token(char **line, t_ast *new_tok)
{
	if (**line == '&')
		return (and_find(line, new_tok));
	else if (**line == '|')
		return (or_find(line, new_tok));
	else if (ft_isalnum(**line))
		return (word_find(line, new_tok));
	else if (**line == '\0')
	{
		new_tok->type = TYPE_END;
		new_tok->value = NULL;
		return (new_tok);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "Error: unexpected symbol %c\n");
		return (NULL);
	}
}

t_ast			*next_token(char **line)
{
	t_ast	*new_tok;

	if ((new_tok = malloc(sizeof(t_ast))) == NULL)
	{
		ft_fprintf(STDERR_FILENO, INTERN_ERR);
		return (NULL);
	}
	new_tok->arg_cmd = NULL;
	new_tok->next = NULL;
	new_tok->left = NULL;
	new_tok->right = NULL;
	consume(line);
	return (find_token(line, new_tok));
}
