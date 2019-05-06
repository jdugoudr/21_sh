/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwa <marwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 12:52:04 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/23 18:05:41 by marwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(char *s, int c)
{
	char	*temp;
	char	*retval;

	temp = (char *)s;
	retval = NULL;
	while (*temp)
	{
		if (*temp == (char)c)
			retval = temp;
		temp++;
	}
	if (*temp == (char)c)
		return (temp);
	return (retval);
}
