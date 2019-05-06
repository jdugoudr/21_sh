/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 22:30:12 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/02 16:26:41 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "parser.h"
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
				// check quotes balance
				ft_printf("\n");
				restore_default_conf();
				parser(g_editor->cmd, shell);//modifier par ju
				ft_printf("\n");
				init_term();
				history_append(shell, g_editor->cmd);
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
