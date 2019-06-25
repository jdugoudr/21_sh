/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:12:43 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/21 13:01:23 by mdaoud           ###   ########.fr       */
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
	if (getcwd(current_dir, PATH_MAX) == NULL)
		current_dir[0] = '\0';
	add_env_var("OLDPWD", current_dir);
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
	if (check_cmd_format(cmd, 0) < 0 && check_cmd_format(cmd, 1) < 0)
	{
		write(STDERR_FILENO, "usage: cd directory\n", 20);
		return (1);
	}
	path = get_path(cmd[1], &print_dir);
	change_directory(path, print_dir);
	free(path);
	return (0);
}
