/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:12:43 by mdaoud            #+#    #+#             */
/*   Updated: 2019/07/07 14:09:14 by jdugoudr         ###   ########.fr       */
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
** Checks if the "cd" command is well formatted.
** replaces special arguments such as "-" and "--" with their respective values
** Calls the function "change_directory()".
*/

int				builtin_cd(char **cmd)
{
	char	*path;
	int		print_dir;

	path = NULL;
	print_dir = 0;
	if (check_cmd_format(cmd, 0) < 0 && check_cmd_format(cmd, 1) < 0)
	{
		ft_dprintf(STDERR_FILENO, "usage: cd directory\n");
		return (1);
	}
	if ((path = get_path(cmd[1], &print_dir)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	if (print_dir && (get_env_ind("OLDPWD") < 0))
	{
		ft_dprintf(STDERR_FILENO, "failed to get old working directory\n");
		free(path);
		return (1);
	}
	change_directory(path, print_dir);
	free(path);
	return (0);
}
