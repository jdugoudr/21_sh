/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 22:30:12 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/30 18:22:38 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include <sys/ioctl.h>

static void		init_buf(char buf[])
{
	size_t	i;

	i = 0;
	while (i < 8)
	{
		buf[i] = 0;
		i++;
	}
}

void				detect_input(t_shell *shell)
{
	char	buf[8];
	int		ret;

	init_buf(buf);
	while ((ret = read(STDIN_FILENO, buf, 7)) != 0)
	{
		if (ret == -1)
			ft_exit("read", 1, EXIT_FAILURE) ;
		else
		{
			ret = dispatch_keypress(shell, *(unsigned long *)buf);
			if (ret > 0)
			{
				exec_cmd();
				history_append(shell, g_editor->cmd);
				// ft_printf("Lines: %d\tColumns: %d\n", g_editor->win_height, g_editor->win_width);
				// ft_printf("Maxlines: %d\nLine: %d\tCol: %d\nCurpos: %d\tsize: %d\n", g_editor->max_line, g_editor->line, g_editor->col, g_editor->cur_pos, g_editor->cmd_sze);
				command_reset();
				shell->hist_ptr = NULL;
				init_buf(buf);
				break ;
			}
			init_buf(buf);
			continue ;
		}
	}
}