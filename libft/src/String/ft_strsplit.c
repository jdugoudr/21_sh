/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwa <marwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:30:32 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/23 18:05:41 by marwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char		**ft_strsplit(char *s, char c)
{
	int		word_count;
	int		word;
	char	**retval;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	word_count = ft_word_count(s, c);
	if (!(retval = malloc((word_count + 1) * sizeof(char *))))
		return (NULL);
	word = 0;
	i = 0;
	while (s[i] && word < word_count)
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		retval[word++] = ft_strsub(s, j, i - j);
	}
	retval[word] = NULL;
	return (retval);
}
