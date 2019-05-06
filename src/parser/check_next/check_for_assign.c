/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_assign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 14:16:26 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/08 13:15:06 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"
#include "libft.h"

int	check_for_assign(t_ast *next, char **line)
{
	(void)line;
	if ((next->type & AFTER_ASS) != 0)
		return (1);
	return (0);
}
