/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:20:33 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/10 19:02:43 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"
#include <sys/ioctl.h>

void			command_write(void)
{
	size_t	i;

	get_editor_dim();
	prompt_display();
	ft_dprintf(g_editor->tty_fd, "%s", g_editor->cmd);
	move_cursor_home();
	i = 0;
	while (i < g_editor->line)
	{
		tputs(tgetstr("do", NULL), 1, tputs_char);
		i++;
	}
	tputs(tgetstr("cr", NULL), 1, tputs_char);
	i = 0;
	while (i < g_editor->col)
	{
		tputs(tgetstr("nd", NULL), 1, tputs_char);
		i++;
	}
}
