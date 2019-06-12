/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:33:18 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/16 16:33:20 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_map(char map[36])
{
	int		i;
	char	c;

	c = 'A';
	i = 0;
	while (i <= 9)
	{
		map[i] = '0' + i;
		i++;
	}
	while (i < 36)
	{
		map[i] = c;
		i++;
		c++;
	}
}

/*
** Maximum value of an usnigned long long is +18,446,744,073,709,551,615.
** lettre_case flag: 1 for uppercase, 0 for lowercase.
** If the nbr is < 0, the conversion will be done on its 2's complement.
*/

char	*ft_ltoa_base(unsigned long long nbr, size_t base, int lettre_case)
{
	char				map[36];
	char				*retval;
	int					i;

	i = 0;
	if ((retval = malloc(65 * sizeof(char))) == NULL)
		return (NULL);
	init_map(map);
	if (base > 36)
		return (NULL);
	while (nbr >= base)
	{
		retval[i++] = map[nbr % base];
		nbr /= base;
	}
	retval[i++] = map[nbr];
	retval[i] = '\0';
	retval = ft_strdup_free(retval);
	retval = ft_strrev(retval);
	if (lettre_case == 0)
		retval = ft_tolower(retval);
	return (retval);
}
