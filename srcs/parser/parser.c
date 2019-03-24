/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:09:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/24 17:51:25 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

/*
** Here we build a list of tokens by calling next_token.
** The last token always have to be of type TYPE_END.
** Each new token have to be check by the previous token
** to see if the new token is enable by grammar.
*/

///////// delete this function before merge master !!
void	print_token(t_ast *tok)
{
	t_ast *el = tok;
	while (el)
	{
		ft_printf("actuel token => %s\n", el->value);
		el = el->next;
	}
}

int	parser(char *line)
{
	t_ast	*token_head;
	t_ast	*token;

	token_head = NULL;
	while ((token = next_token(&line)) && token->type != TYPE_END)
	{
		token->next = token_head;
		token_head = token;
	}
	if (token)
	{
		token->next = token_head;
		token_head = token;
		print_token(token_head);/////// this is for debug
	}
	else
		ft_printf("HOLLY SHIT ! A problems appeared !\n");
	del_ast(&token_head);
	return (0);
}
