/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 17:08:26 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/13 19:54:44 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

void			prompt_display(void)
{
	// ft_dprintf(g_editor->tty_fd, "%s", g_editor->prompt);

	ft_dprintf(g_editor->tty_fd, "%s➜  %s%s%s ", GREEN, RED, g_editor->prompt, RES_COL);
}
