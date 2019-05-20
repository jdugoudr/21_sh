/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:29:23 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 17:52:57 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

static size_t			get_enter_count(char *str)
{
	size_t		i;
	size_t		retval;
	size_t		c;

	retval = 0;
	c = g_editor->offset;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || c == g_editor->win_width - 1)
		{
			retval++;
			c = 0;
		}
		else
			c++;
		i++;
	}
	return (retval);
}

void					clear_string(char *str)
{
	size_t	i;
	size_t	line_count;

	if (!ft_strchr(str, '\n'))
	{
		line_count = ft_strlen(str) + g_editor->offset;
		line_count = line_count / g_editor->win_width;
	}
	else
		line_count = get_enter_count(str);
	i = 0;
	while (i <= line_count)
	{
		tputs(tgetstr("dl", NULL), 1, tputs_char);
		if (i < line_count)
			tputs(tgetstr("up", NULL), 1, tputs_char);
		i++;
	}
	tputs(tgetstr("cr", NULL), 1, tputs_char);
}
