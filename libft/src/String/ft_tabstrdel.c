/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstrdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:56:48 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/28 17:11:03 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	freebysize(char **str, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
}

static void	freebynull(char **str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
	}
}

void		ft_tabstrdel(char ***str, size_t size)
{
	if (str && *str)
	{
		if (size)
			freebysize(*str, size);
		else
			freebynull(*str);
		free(*str);
		*str = NULL;
	}
}
