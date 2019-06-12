/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwa <marwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:46:42 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/23 18:05:41 by marwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	unsigned int	it;
	char			*retval;

	if (s == NULL)
		return (NULL);
	it = 0;
	if ((retval = malloc((ft_strlen(s) + 1) * sizeof(char))) == NULL)
		return (NULL);
	while (s[it])
	{
		retval[it] = f(it, s[it]);
		it++;
	}
	retval[it] = '\0';
	return (retval);
}
