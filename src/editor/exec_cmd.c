/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:59:10 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/03 14:52:13 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			exec_cmd(t_shell *shell)
{
		(void)shell;
	if (ft_strequ(g_editor->cmd, "exit"))
	{
		free_shell(shell);
		ft_exit(NULL, 1, 1, EXIT_SUCCESS);
	}
	else
	{
		dprintf(STDOUT_FILENO, "Executing \"%s\"\n", g_editor->cmd);
	}

}