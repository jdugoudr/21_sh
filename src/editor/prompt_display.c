/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 17:08:26 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 15:13:29 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include <stdio.h> //

void			prompt_display(void)
{
	dprintf(g_editor->tty_fd, "%s", g_editor->prompt);
}