/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_his_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 16:46:50 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/30 16:57:44 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			set_last_history_entry(t_shell *shell)
{
	if (shell->hist == NULL)
		return ;
	shell->hist_ptr = shell->hist;
	while (shell->hist_ptr->next != NULL)
		shell->hist_ptr = shell->hist_ptr->next;
}