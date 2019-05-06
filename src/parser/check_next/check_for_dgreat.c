/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_dgreat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:44:08 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/08 13:17:13 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"

int	check_for_dgreat(t_ast *next, char **line)
{
	(void)line;
	if ((next->type & AFTER_DGREAT) == 0)
		return (1);
	return (0);
}
