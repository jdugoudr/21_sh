/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 00:52:22 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/06 10:51:08 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include <limits.h>
#include "editor.h"
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static void		set_oldpwd(char *val)
{
	int			ind;
	char		*var;

	ind = get_env_ind("OLDPWD");
	free(g_shell->env[ind]);
	var = ft_strjoin("OLDPWD=", val, 0);
	g_shell->env[ind] = var;
}

static void		set_pwd()
{
	int			ind;
	char		*var;
	char		curr_dir[PATH_MAX];

	getcwd(curr_dir, PATH_MAX);
	if ((ind = get_env_ind("PWD")) < 0)
	{
		add_env_var("PWD", curr_dir);
		return ;
	}
	free(g_shell->env[ind]);
	var = ft_strjoin("PWD=", curr_dir, 0);
	g_shell->env[ind] = var;
}

/*
** Changes the current working directory.
** Updates the environment variables "PWD" and "OLDPWD".
** In case of error, prints the appropriate error message.
*/

void			change_directory(char *path, int print_dir)
{
	char	old_dir[PATH_MAX];

	if (print_dir)
		ft_dprintf(STDOUT_FILENO, "%s\n", path);
	getcwd(old_dir, PATH_MAX);
	if (chdir(path) == -1)
	{
		if ((access(path, F_OK) == -1))
			ft_dprintf(STDERR_FILENO, "cd: no such file or directory: %s\n",\
				path);
		else if ((access(path, R_OK) == -1))
			ft_dprintf(STDERR_FILENO, "cd: permission denied: %s\n", path);
		else
			ft_dprintf(STDERR_FILENO, "cd: not a directory: %s\n", path);
		return ;
	}
	set_oldpwd(old_dir);
	set_pwd();
}
