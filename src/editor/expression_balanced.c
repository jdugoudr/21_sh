/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_balanced.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:04:41 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/09 17:35:32 by mdaoud           ###   ########.fr       */
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
		// ft_printf("setting open quotes\n");
		g_editor->quotes |= PARANTH;
	}
}

static void		close_paranthesis(void)
{
	if ((g_editor->quotes & (SINGLE_Q | DOUBLE_Q)) == 0)
		g_editor->quotes |= ~PARANTH;
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

// int				quotes_balanced(void)
// {
// 	size_t	i;
// 	char	c;

// 	i = 0;
// 	while (g_editor->cmd[i])
// 	{
// 		c = g_editor->cmd[i];
// 		if (c == '\'')
// 		{
// 			if (g_editor->quotes == 0)
// 				g_editor->quotes = 1;
// 			else if (g_editor->quotes == 1)
// 				g_editor->quotes = 0;
// 		}
// 		else if (c == '\"')
// 		{
// 			if (g_editor->quotes == 0)
// 				g_editor->quotes = 2;
// 			else if (g_editor->quotes == 2)
// 				g_editor->quotes = 0;
// 		}
// 		i++;
// 	}
// 	return (g_editor->quotes == 0);
// }