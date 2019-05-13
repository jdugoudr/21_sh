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
	ft_strcpy(g_editor->prompt, dir_name + root_dir);
	g_editor->offset = ft_strlen(g_editor->prompt) + 4;
}