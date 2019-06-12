/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:12:27 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/14 12:40:20 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*retval;

	if ((retval = malloc((size + 1) * sizeof(char))) == NULL)
		return (NULL);
	ft_memset(retval, 0, size + 1);
	return (retval);
}
