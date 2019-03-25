/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:58:27 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/25 18:31:51 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "del_ast.h"
#include "libft.h"

void	del_token(t_ast **el)
{
	if (*el == NULL)
		return ;
	free((*el)->value);
	ft_tabstrdel(&((*el)->arg_cmd), 0);
	free((*el));
	*el = NULL;
}
