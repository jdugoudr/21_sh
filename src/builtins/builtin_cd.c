/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:12:43 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/31 15:53:43 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "shell21.h"
#include "libft.h"
#include "sh_error.h"

static char		*get_path(char *str, int *print_dir)
{
	char	*path;

	if (str == NULL || ft_strequ("--", str))
		path = get_env_value("HOME");
	else if (ft_strequ("-", str))
	{
		*print_dir = 1;
		path = get_env_value("OLDPWD");
	}
	else
		path = ft_strdup(str);
	return (path);
}

/*
** If the "cd" is used with no OLDPWD variable,
**	OLDPWD is set to the current working directory.
*/

static void		repair_oldpwd(void)
{
	char	current_dir[PATH_MAX];

	if (get_env_ind("OLDPWD") >= 0)
		return ;
	getcwd(current_dir, PATH_MAX);
	add_env_var("OLDPWD", current_dir);
}

static char		*get_sy_link(char *str)
{
	char		*path;
	struct stat	st;

	path = NULL;
	if (lstat(str, &st) < 0)
	{
		if ((access(str, F_OK) == -1))
			ft_dprintf(STDERR_FILENO, "cd: no such file or directory: %s\n",\
				str);
		else
			ft_dprintf(STDERR_FILENO, INTERN_ERR);
	}
	else if ((st.st_mode & S_IFMT) == S_IFLNK)
	{
		if ((path = ft_strnew(256)) == NULL)
			ft_dprintf(STDERR_FILENO, INTERN_ERR);
		else
			readlink(str, path, 256);
	}
	else
		path = ft_strdup(str);
	free(str);
	return (path);
}

static int		loop_arg(char **cmd, char **path, int *print_dir, int *sy_link)
{
	int i;

	i = 1;
	if (ft_strequ("-P", cmd[1]))
	{
		*sy_link = 1;
		i = 2;
	}
	else if (ft_strequ("-L", cmd[1]))
		i = 2;
	while (cmd[i])
	{
		if (ft_strequ("--", cmd[i]) == 0)
			break ;
		i++;
	}
	if ((*path = get_path(cmd[i], print_dir)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (0);
}

/*
** Checks if the "cd" command is well formatted.
** replaces special arguments such as "-" and "--" with their respective values
** Calls the function "change_directory()".
*/

int				builtin_cd(char **cmd)
{
	char	*path;
	int		print_dir;
	int		sy_link;

	sy_link = 0;
	path = NULL;
	print_dir = 0;
	repair_oldpwd();
	if (check_cmd_format(cmd, 0) == -1 && check_cmd_format(cmd, 1) == -1
		&& check_cmd_format(cmd, 2) == -1 && check_cmd_format(cmd, 3) == -1)
	{
		write(STDERR_FILENO, "usage: cd [-L | -P] directory\n", 20);
		return (1);
	}
	if (loop_arg(cmd, &path, &print_dir, &sy_link))
		return (1);
	if (sy_link && (path = get_sy_link(path)) == NULL)
		return (1);
	change_directory(path, print_dir);
	free(path);
	return (0);
}
