/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_erase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:44:06 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/30 18:44:50 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void		command_erase(void)
{
	size_t	i;

	i = g_editor->line;
	while(i < g_editor->max_line)
	{
		tputs(tgetstr("do", NULL), 1, tputs_char);
		i++;
	}
	i = 0;
	while (i <= g_editor->max_line)
	{
		tputs(tgetstr("dl", NULL), 1, tputs_char);
		if (i < g_editor->max_line)
			tputs(tgetstr("up", NULL), 1, tputs_char);
		i++;
	}
}