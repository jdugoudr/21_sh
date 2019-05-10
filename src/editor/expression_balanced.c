/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression_balanced.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:04:41 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 17:43:25 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"


static void		single_quote(void)
{
	if ((g_editor->quotes & (SINGLE_Q | DOUBLE_Q)) == 0)
		g_editor->quotes |= SINGLE_Q;
	else if ((g_editor->quotes | SINGLE_Q) != 0)
		g_editor->quotes &= ~SINGLE_Q;
}

static void		double_quote(void)
{
	if ((g_editor->quotes & (SINGLE_Q | DOUBLE_Q)) == 0)
		g_editor->quotes |= DOUBLE_Q;
	else if ((g_editor->quotes | DOUBLE_Q) != 0)
		g_editor->quotes &= ~DOUBLE_Q;
}

static void		open_paranthesis(void)
{
	if ((g_editor->quotes & (SINGLE_Q | DOUBLE_Q)) == 0)
	{
		g_editor->quotes |= PARANTH;
		g_editor->open_subsh++;
	}
}

static void		close_paranthesis(void)
{
	if ((g_editor->quotes & (SINGLE_Q | DOUBLE_Q)) == 0)
	{
		if (g_editor->open_subsh <= 0)
			return ;
		g_editor->open_subsh--;
		if (g_editor->open_subsh == 0)
			g_editor->quotes &= ~PARANTH;
	}
}

static int		expression_result(void)
{
	return (g_editor->quotes == 0);
}

int				expression_balanced(void)
{
	size_t	i;
	char	c;

	i = 0;
	while (g_editor->cmd[i])
	{
		c = g_editor->cmd[i];
		if (c == '\'')
			single_quote();
		else if (c == '\"')
			double_quote();
		else if (c == '(')
			open_paranthesis();
		else if (c == ')')
			close_paranthesis();
		i++;
	}
	return (expression_result());
}
