/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwa <marwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 12:52:04 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/23 18:05:41 by marwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *haystack, char *needle)
{
	int		i;
	int		j;
	char	*temp;

	temp = (char *)haystack;
	if (!*needle)
		return (temp);
	i = 0;
	while (temp[i] != '\0')
	{
		j = 0;
		while (needle[j] == temp[i + j])
		{
			if (needle[j + 1] == '\0')
				return (temp + i);
			j++;
		}
		i++;
	}
	return (0);
}
