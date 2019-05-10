/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_reset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:26:11 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/12 17:27:44 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

/*
** set the prompt to display the current working directory.
*/

void			prompt_reset(void)
{
	ft_bzero(g_editor->prompt, PATH_MAX);
	if (getcwd(g_editor->prompt, PATH_MAX) == NULL)
	{
		prompt_set("$>> ");
		return ;
	}
	ft_strcat(g_editor->prompt, "$ ");
	g_editor->offset = ft_strlen(g_editor->prompt);
	// ft_bzero(g_editor->prompt, PATH_MAX);
	// 	prompt_set("$>> ");
}