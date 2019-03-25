/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:46:35 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/25 19:27:13 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_define.h"
#include "check_next.h"

int	check_for_word(t_ast *next)
{
	if ((next->type & AFTER_WORD))
		return (1);
	return (0);
}
