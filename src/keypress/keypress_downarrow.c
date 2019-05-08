/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_downarrow.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:36:58 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/11 18:04:33 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			keypress_downarrow(t_shell *shell)
{
	if (shell->hist == NULL || shell->hist_ptr == NULL)
		return ;
	if (shell->hist_ptr->next != NULL)
	{
		shell->hist_ptr = shell->hist_ptr->next;
		command_set(shell->hist_ptr->name, 1);
	}
	else
	{
		command_erase();
		command_reset();
		display_prompt();
		shell->hist_ptr = NULL;
	}
}