/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 12:35:08 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/29 16:58:02 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"

int	check_for_pipe(t_ast *next, char **line)
{
	(void)line;
	if ((next->type & AFTER_PIPE) == 0)
		return (1);
	return (0);
}
