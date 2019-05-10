/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:26:11 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 18:23:17 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "editor.h"

void			keypress_end(void)
{
	command_erase();
	g_editor->cur_pos = g_editor->cmd_sze;
	command_write();
}