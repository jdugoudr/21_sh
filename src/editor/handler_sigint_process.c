/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigint_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:29:47 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/24 17:44:11 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include <signal.h>
#include <libft.h>

void			handler_sigint_process(int signo)
{
	if (signo == SIGINT)
	{
		g_editor->flag_sigint = 1;
		ft_dprintf(STDOUT_FILENO, "\n");
		command_reset();
	}
}
