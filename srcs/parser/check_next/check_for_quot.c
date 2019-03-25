/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_quot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:51:43 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/25 18:19:38 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_define.h"
#include "check_next.h"

int	check_for_quot(t_ast *next)
{
	if (next->type == SUB_SHELL || next->type == NAME_TOK
			|| next->type == ASSIGN_TOK)
		return (1);
	return (0);
}
