/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:31:24 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/21 16:06:57 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **alst)
{
	t_list	*next_ptr;

	while (*alst)
	{
		next_ptr = (*alst)->next;
		free((*alst)->content);
		(*alst)->content = NULL;
		free(*alst);
		*alst = next_ptr;
	}
}
