/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:16:57 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/27 18:26:37 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

/*
** Checks if a given command has the exactly @param_num number of parameters.
** @returns:	-1	invalid command format.
**				1	valid command format.
*/

int		check_cmd_format(char **cmd, size_t param_num)
{
	size_t	i;

	i = 0;
	while (cmd[i] != NULL)
		i++;
	if (i != param_num + 1)
		return (-1);
	return (1);
}
