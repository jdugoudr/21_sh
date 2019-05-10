/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_uparrow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:33:49 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 18:25:58 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "editor.h"
#include "shell21.h"

void			keypress_uparrow(void)
{
	if (g_shell->hist == NULL)
		return ;
	if (g_shell->hist_ptr == NULL)
	{
		g_shell->hist_ptr = g_shell->hist;
		while (g_shell->hist_ptr->next != NULL)
			g_shell->hist_ptr = g_shell->hist_ptr->next;
		command_set(g_shell->hist_ptr->name, 1);
	}
	else if (g_shell->hist_ptr->prev != NULL)
	{
		g_shell->hist_ptr = g_shell->hist_ptr->prev;
		command_set(g_shell->hist_ptr->name, 1);
	}
}
