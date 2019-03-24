/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstr_realloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:06:11 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/15 15:26:15 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabstr_realloc(char **tab, int old_size, int new_size)
{
	char	**new_tab;
	int		i;

	i = 0;
	if ((new_tab = (char **)malloc((new_size + 1) * sizeof(char *))) == NULL)
		return (NULL);
	while (i < old_size)
	{
		new_tab[i] = tab[i];
		i++;
	}
	free(tab);
	while (i < new_size)
	{
		new_tab[i] = NULL;
		i++;
	}
	new_tab[new_size] = NULL;
	return (new_tab);
}
