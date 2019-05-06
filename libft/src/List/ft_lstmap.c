/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:31:24 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/22 16:19:18 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;
	t_list	*retval;

	temp = f(lst);
	retval = temp;
	lst = lst->next;
	while (lst)
	{
		ft_lstappend(&temp, (f)(lst));
		lst = lst->next;
	}
	return (retval);
}
