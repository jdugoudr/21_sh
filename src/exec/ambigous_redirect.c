/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambigous_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 16:47:05 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 16:47:46 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec_cmd.h"
#include "sh_error.h"
#include "fcntl.h"
#include "libft.h"
#include "ast.h"

int	ambigous_redirect(t_ast *token)
{
	while (token->next)
	{
		if (token->next->level_prior == level_4)
		{
			if (token->type != WORD_TOK
				|| (token->prev && token->prev->type == WORD_TOK))
			{
				ft_dprintf(STDERR_FILENO, AMBI_REDIR);
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}
