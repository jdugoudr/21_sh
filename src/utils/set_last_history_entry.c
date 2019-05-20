/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_last_history_entry.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 16:46:50 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 18:22:01 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			set_last_history_entry(void)
{
	if (g_shell->hist == NULL)
		return ;
	g_shell->hist_ptr = g_shell->hist;
	while (g_shell->hist_ptr->next != NULL)
		g_shell->hist_ptr = g_shell->hist_ptr->next;
}
