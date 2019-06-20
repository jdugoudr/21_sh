/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_editor_dim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 17:10:21 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/20 11:23:31 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

static void		calc_dim(void)
{
	int		x;

	x = g_editor->cmd_sze + g_editor->offset - g_editor->win_width;
	x = (x < 0 ? 0 : x);
	g_editor->max_line = x / g_editor->win_width;
	if (x % g_editor->win_width || (x % g_editor->win_height == 0
			&& g_editor->cmd_sze + g_editor->offset > g_editor->win_width))
		g_editor->max_line++;
	x = g_editor->cur_pos + g_editor->offset;
	g_editor->line = x / g_editor->win_width;
	g_editor->col = x % g_editor->win_width;
}

static void		get_col_row(void)
{
	size_t	i;

	g_editor->col = g_editor->offset;
	g_editor->line = 0;
	i = 0;
	while (g_editor->cmd[i] && i < g_editor->cur_pos)
	{
		if (g_editor->cmd[i] == '\n'
			|| g_editor->col == g_editor->win_width - 1)
		{
			g_editor->line++;
			g_editor->col = 0;
		}
		else
			g_editor->col++;
		i++;
	}
}

void			get_editor_dim(void)
{
	size_t	i;

	if (!ft_strchr(g_editor->cmd, '\n'))
	{
		calc_dim();
		return ;
	}
	g_editor->max_line = 0;
	g_editor->col = g_editor->offset;
	g_editor->line = 0;
	i = 0;
	while (g_editor->cmd[i])
	{
		if (g_editor->cmd[i] == '\n'
			|| g_editor->col == g_editor->win_width - 1)
		{
			g_editor->max_line++;
			g_editor->line = 0;
			g_editor->col = 0;
		}
		else
			g_editor->col++;
		i++;
	}
	get_col_row();
}
