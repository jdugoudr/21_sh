/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_and_or.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:26:13 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/26 09:49:43 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"

int	check_for_and_or(t_ast *next)
{
	if ((next->type & AFTER_ANOR) == 0)
		return (1);
	return (0);
}
