/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 00:52:22 by mdaoud            #+#    #+#             */
/*   Updated: 2019/07/07 14:12:02 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include <limits.h>
#include "editor.h"
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "sh_error.h"

static int		set_oldpwd(char *val)
{
	int			ind;
	char		*var;

	ind = get_env_ind("OLDPWD");
	if (ind < 0)
	{
		if (ind == -1 || add_env_var("OLDPWD", val))
		{
			ft_dprintf(STDERR_FILENO, "Could not set the OLDPWD\n");
			return (-1);
		}
		return (0);
	}
	free(g_shell->env[ind]);
	var = ft_strjoin("OLDPWD=", val, 0);
	g_shell->env[ind] = var;
	return (0);
}

static int		set_pwd(char *curr_dir)
{
	int			ind;
	char		*var;

	if ((ind = get_env_ind("PWD")) < 0)
	{
		if (ind == -1 || add_env_var("PWD", curr_dir))
		{
			ft_dprintf(STDERR_FILENO, "Could not set the PWD variable\n");
			return (-1);
		}
		return (0);
	}
	free(g_shell->env[ind]);
	if ((var = ft_strjoin("PWD=", curr_dir, 0)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (-1);
	}
	g_shell->env[ind] = var;
	return (0);
}

/*
** Changes the current working directory.
** Updates the environment variables "PWD" and "OLDPWD".
** In case of error, prints the appropriate error message.
*/

void			change_directory(char *path, int print_dir)
{
	char	dir[PATH_MAX];
	int		valid_getcwd;

	valid_getcwd = getcwd(dir, PATH_MAX) != NULL;
	if (print_dir)
		ft_dprintf(STDOUT_FILENO, "%s\n", path);
	if (chdir(path) == -1)
	{
		if ((access(path, F_OK) == -1))
			ft_dprintf(STDERR_FILENO, "cd: no such file or directory: %s\n",
				path);
		else if ((access(path, R_OK) == -1))
			ft_dprintf(STDERR_FILENO, "cd: permission denied: %s\n", path);
		else
			ft_dprintf(STDERR_FILENO, "cd: not a directory: %s\n", path);
		return ;
	}
	if (valid_getcwd)
		set_oldpwd(dir);
	valid_getcwd = getcwd(dir, PATH_MAX) != NULL;
	if (valid_getcwd)
		set_pwd(dir);
}
