/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwa <marwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 11:47:34 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/23 17:55:34 by marwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		**ft_lstsplit(char *s, char c)
{
	t_list	**retval;
	char	*sub;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	if ((retval = malloc(sizeof(t_list *))) == NULL)
		return (NULL);
	*retval = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		sub = ft_strsub(s, j, i - j);
		ft_lstappend(retval, ft_lstnew((void *)sub, ft_strlen(sub) + 1));
	}
	return (retval);
}
