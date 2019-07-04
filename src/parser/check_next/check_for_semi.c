/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_semi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:12:30 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/08 13:16:33 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"

int	check_for_semi(t_ast *next, char **line)
{
	(void)line;
	if ((next->type & AFTER_SEMI))
		return (1);
	return (0);
}
