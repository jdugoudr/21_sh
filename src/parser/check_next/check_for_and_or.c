/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_and_or.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:26:13 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/08 13:15:51 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"

int	check_for_and_or(t_ast *next, char **line)
{
	(void)line;
	if ((next->type & AFTER_ANOR) == 0)
		return (1);
	return (0);
}
