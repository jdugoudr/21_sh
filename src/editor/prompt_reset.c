/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:09:33 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/09 15:06:08 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

/*
** set the prompt to display the current working directory.
*/

void			prompt_reset(void)
{
	char		cwd[PATH_MAX];
	char		*dir_name;
	int			root_dir;

	ft_bzero(g_editor->prompt, PATH_MAX);
	if (getcwd(g_editor->prompt, PATH_MAX) == NULL)
	{
		prompt_set("$>> ");
		return ;
	}
	getcwd(cwd, PATH_MAX);
	root_dir = !ft_strequ("/", cwd);
	dir_name = ft_strrchr(cwd, '/');
	if (dir_name == NULL)
		dir_name = cwd;
	ft_strcpy(g_editor->prompt, "-> ");
	ft_strcat(g_editor->prompt, dir_name + root_dir);
	ft_strcat(g_editor->prompt, ": ");
	g_editor->offset = ft_strlen(g_editor->prompt);
}
