/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:10:04 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/24 17:57:14 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token_define.h"
#include "libft.h"

t_ast	*word_find(char **line, t_ast *tok)
{
	int	i;

	i = 1;
	while (ft_isalnum((*line)[i]))
		i++;
	tok->type = WORD_TOK;
	tok->value = ft_strndup(*line, i);
	(*line) += i;
	return (tok);
}
