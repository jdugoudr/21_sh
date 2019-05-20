/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_balanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:34:53 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 18:11:05 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
** Function to check whether the command has a propre quotes balance.
** @return:		0: quotes are not balanced.
**				1: quotes are balanced.
*/

int				quotes_balanced(void)
{
	size_t	i;
	char	c;

	i = 0;
	while (g_editor->cmd[i])
	{
		c = g_editor->cmd[i];
		if (c == '\'')
		{
			if (g_editor->quotes == 0)
				g_editor->quotes = 1;
			else if (g_editor->quotes == 1)
				g_editor->quotes = 0;
		}
		else if (c == '\"')
		{
			if (g_editor->quotes == 0)
				g_editor->quotes = 2;
			else if (g_editor->quotes == 2)
				g_editor->quotes = 0;
		}
		i++;
	}
	return (g_editor->quotes == 0);
}
