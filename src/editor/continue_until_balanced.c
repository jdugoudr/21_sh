/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_until_balanced.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:22:56 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 15:36:15 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			continue_until_balanced(void)
{
	int	q_flag;

	q_flag = g_editor->quotes;
	ft_printf("%d", g_editor->quotes);
	if (q_flag == 1)
		prompt_set("quote> ");
	else if (q_flag == 2)
		prompt_set("dquote> ");
	else if (q_flag == 4)
		prompt_set("subsh> ");
	else if ((q_flag | (SINGLE_Q | PARANTH)) != 0)
		prompt_set("subsh quote> ");
	else if ((q_flag | (DOUBLE_Q | PARANTH)) != 0)
		prompt_set("subsh dquote> ");
	dprintf(g_editor->tty_fd, "\n");
	command_reset();
}