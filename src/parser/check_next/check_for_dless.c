/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_dless.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:37:52 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/08 13:16:48 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"

int	check_for_dless(t_ast *next, char **line)
{
	(void)line;
	if ((next->type & AFTER_DLESS) == 0)
		return (1);
	return (0);
}
