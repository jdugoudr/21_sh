/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 14:11:30 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/08 13:15:37 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"

int	check_for_name(t_ast *next, char **line)
{
	(void)line;
	if ((next->type & AFTER_NAME) == 0)
		return (1);
	return (0);
}
