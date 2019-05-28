/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:52:40 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/28 15:50:01 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

/*
** Check if a command only exists of spaces and semicolons
*/

int			is_empty_cmd(void)
{
	size_t	i;

	i = 0;
	while (g_editor->cmd[i] != '\0')
	{
		if (g_editor->cmd[i] != ' ' && g_editor->cmd[i] != ';')
			return (0);
		i++;
	}
	ft_dprintf(g_editor->tty_fd, "\n");
	command_reset();
	return (1);
}
