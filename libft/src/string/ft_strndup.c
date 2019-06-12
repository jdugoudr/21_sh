/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:52:10 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/07 16:16:24 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *src, size_t len)
{
	char	*dest;
	size_t	len_src;

	len_src = ft_strlen(src);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (dest);
	if (len_src > len)
		ft_strncpy(dest, src, len);
	else
	{
		ft_strncpy(dest, src, len_src);
		while (len_src < len)
		{
			dest[len_src] = '\0';
			len_src++;
		}
	}
	dest[len] = '\0';
	return (dest);
}
