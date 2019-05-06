/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 13:18:22 by mdaoud            #+#    #+#             */
/*   Updated: 2019/01/05 13:40:06 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char *s1, char *s2, int n)
{
	size_t	len1;
	size_t	len2;
	char	*retval;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	retval = malloc((len1 + len2 + 1) * sizeof(char));
	if (!retval)
		return (NULL);
	ft_memcpy(retval, s1, len1);
	ft_memcpy(retval + len1, s2, len2);
	retval[len1 + len2] = '\0';
	if (n & 1)
		ft_strdel(&s1);
	if (n & 2)
		ft_strdel(&s2);
	return (retval);
}
