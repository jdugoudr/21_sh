/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:58:50 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/26 10:05:16 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_define.h"
#include "check_next.h"

int	check_for_sub(t_ast *next)
{
	if (next->type & AFTER_SUB)
		return (1);
	return (0);
}
