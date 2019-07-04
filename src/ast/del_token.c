/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:58:27 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/02 18:28:13 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

static void	del_tab(char **tabs)
{
	int	i;

	i = 0;
	while (tabs && tabs[i])
	{
		free(tabs[i]);
		i++;
	}
	free(tabs);
}

void		del_token(t_ast **el)
{
	if (*el == NULL)
		return ;
	free((*el)->value);
	del_tab((*el)->arg_cmd);
	del_ast(&(*el)->head_sub);
	free((*el));
	*el = NULL;
}
