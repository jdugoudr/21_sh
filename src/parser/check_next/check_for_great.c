/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_great.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:46:19 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/08 13:17:30 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"

int	check_for_great(t_ast *next, char **line)
{
	(void)line;
	if ((next->type & AFTER_GREAT) == 0)
		return (1);
	return (0);
}
