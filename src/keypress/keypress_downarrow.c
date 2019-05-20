/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_downarrow.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:36:58 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 18:13:57 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "shell21.h"
#include "editor.h"

void			keypress_downarrow(void)
{
	if (g_shell->hist == NULL || g_shell->hist_ptr == NULL)
		return ;
	if (g_shell->hist_ptr->next != NULL)
	{
		g_shell->hist_ptr = g_shell->hist_ptr->next;
		command_set(g_shell->hist_ptr->name, 1);
	}
	else
	{
		command_erase();
		command_reset();
		prompt_display();
		g_shell->hist_ptr = NULL;
	}
}
