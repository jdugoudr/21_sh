/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_uparrow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:33:49 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/11 18:04:55 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			keypress_uparrow(t_shell *shell)
{
	if (shell->hist == NULL)
		return ;
	if (shell->hist_ptr == NULL)
	{
		shell->hist_ptr = shell->hist;
		while (shell->hist_ptr->next != NULL)
			shell->hist_ptr = shell->hist_ptr->next;
		command_set(shell->hist_ptr->name, 1);
	}
	else if (shell->hist_ptr->prev != NULL)
	{
		shell->hist_ptr = shell->hist_ptr->prev;
		command_set(shell->hist_ptr->name, 1);
	}
}
