/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 11:47:34 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/21 16:13:29 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** "lst->content_size - 1" because the content is null-terminated
*/

void	ft_lstprint_node(t_list *lst)
{
	size_t		i;

	if (lst == NULL)
		return ;
	i = 0;
	while (i < lst->content_size - 1)
	{
		ft_putchar(*(char *)(lst->content + i));
		i++;
	}
	ft_putchar('\n');
}
