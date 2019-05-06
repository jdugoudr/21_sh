/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:54:51 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/21 16:06:15 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_lst_remove_content(t_list **node)
{
	if (node == NULL || *node == NULL)
		return ;
	free((*node)->content);
	(*node)->content = NULL;
	free(*node);
	*node = NULL;
}

void				ft_lstremove(t_list **list, t_list **node)
{
	t_list		*it;

	if (*node == *list)
	{
		*list = (*node)->next;
		ft_lst_remove_content(node);
		return ;
	}
	it = *list;
	while (it->next != *node)
		it = it->next;
	it->next = (*node)->next;
	ft_lst_remove_content(node);
}
