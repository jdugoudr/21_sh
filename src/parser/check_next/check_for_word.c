/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:46:35 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/08 15:45:15 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_define.h"
#include "check_next.h"

int	check_for_word(t_ast *next, char **line)
{
	(void)line;
	if ((next->type & AFTER_WORD))
		return (1);
	return (0);
}
