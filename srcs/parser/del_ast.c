/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:25:38 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/24 17:38:15 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_define.h"
#include "parser.h"
#include "libft.h"

void	del_ast(t_ast **ast_head)
{
	t_ast	*el;
	t_ast	*el_next;

	el = *ast_head;
	while (el)
	{
		el_next = el->next;
		free(el->value);
		ft_tabstrdel(&(el->arg_cmd), 0);
		free(el);
		el = el_next;
	}
	*ast_head = NULL;
}
