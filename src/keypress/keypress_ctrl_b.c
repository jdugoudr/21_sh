/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_ctrl_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:41:43 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 18:13:30 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "editor.h"
#include "libft.h"

void			keypress_ctrl_b(size_t start, size_t end)
{
	char	tmp[ARG_MAX + 1];
	size_t	i;

	if (start == end)
		return ;
	ft_memset(g_editor->cpy_buff, '\0', ARG_MAX + 1);
	ft_memset(tmp, '\0', ARG_MAX + 1);
	i = 0;
	while (start < end)
	{
		tmp[i] = g_editor->cmd[start];
		start++;
		i++;
	}
	ft_strcpy(g_editor->cpy_buff, tmp);
}
