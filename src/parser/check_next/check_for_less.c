/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_less.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:43:03 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/08 13:17:00 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"

int	check_for_less(t_ast *next, char **line)
{
	(void)line;
	if ((next->type & AFTER_LESS) == 0)
		return (1);
	return (0);
}
