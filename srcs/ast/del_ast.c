/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:25:38 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/25 17:28:22 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "del_ast.h"
#include "libft.h"

void	del_ast(t_ast **ast_head)
{
	t_ast	*el;
	t_ast	*el_next;

	el = *ast_head;
	while (el)
	{
		el_next = el->next;
		del_token(&el);
		el = el_next;
	}
	*ast_head = NULL;
}
