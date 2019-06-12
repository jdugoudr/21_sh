/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:11:19 by mdaoud            #+#    #+#             */
/*   Updated: 2018/12/16 16:31:05 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Very basic implementaion of the pow function.
** Only takes positive power values.
*/

long long	ft_pow(int nbr, int power)
{
	int			i;
	long long	retval;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	i = 1;
	retval = nbr;
	while (i++ < power)
		retval *= nbr;
	return (retval);
}
