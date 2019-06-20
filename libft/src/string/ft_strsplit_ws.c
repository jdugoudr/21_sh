/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_ws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 11:34:20 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/20 15:25:32 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_cpt_word(char *str)
{
	int i;
	int cmp;
	int len_w;

	cmp = 0;
	i = 0;
	len_w = 0;
	while (str[i] != '\0')
	{
		while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			&& str[i] != '\0')
			i++;
		while (str[i] >= 33 && str[i] <= 126 && str[i] != '\0')
		{
			len_w++;
			cmp++;
			i++;
		}
		if (len_w != 0)
			cmp = cmp + 1 - len_w;
		len_w = 0;
	}
	return (cmp);
}

static void		ft_word_cp(char *str, char **str_, int w)
{
	int		i;
	int		j;
	int		c_w;

	j = 0;
	c_w = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] != '\0')
	{
		while (str[j + i] != ' ' && str[j + i] != '\t'
			&& str[j + i] != '\n' && str[j + i] != '\0')
			j++;
		if (!(str_[w] = (char *)malloc(sizeof(char *) * j)))
			return ;
		while (c_w < j)
		{
			str_[w][c_w] = str[i + c_w];
			c_w++;
		}
		str_[w][c_w] = '\0';
		ft_word_cp(str + i + j, str_, w + 1);
	}
}

char			**ft_strsplit_ws(char *str)
{
	int		nb_word;
	char	**str_;

	str_ = NULL;
	if (str == 0)
		return (str_);
	nb_word = ft_cpt_word(str);
	str_ = (char **)malloc(sizeof(*str_) * (nb_word + 1));
	if (str_ == NULL)
		return (str_);
	ft_word_cp(str, str_, 0);
	str_[nb_word] = 0;
	return (str_);
}
