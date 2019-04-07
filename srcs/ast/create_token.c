/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:12:35 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/07 10:46:39 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "token_define.h"
#include "sh_error.h"
#include "libft.h"

t_ast	*create_token()
{
	t_ast	*new_tok;

	if ((new_tok = malloc(sizeof(t_ast))) == NULL)
	{
		ft_fprintf(STDERR_FILENO, INTERN_ERR);
		return (NULL);
	}
	new_tok->arg_cmd = NULL;
	new_tok->next = NULL;
	new_tok->prev = NULL;
	new_tok->left = NULL;
	new_tok->right = NULL;
	new_tok->value = NULL;
	new_tok->f_exec = NULL;
	return (new_tok);
}
