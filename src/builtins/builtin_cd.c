/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:12:43 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/13 19:35:44 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include "shell21.h"
#include "libft.h"

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

/*
** Checks if the "cd" command is well formatted.
** replaces special arguments such as "-" and "--" with their respective values
** Calls the function "change_directory()".
*/

int				builtin_cd(char **cmd)
{
	char	*path;
	int		print_dir;

	print_dir = 0;
	repair_oldpwd();
	if (check_cmd_format(cmd, 0) == -1 && check_cmd_format(cmd, 1) == -1)
	{
		ft_dprintf(STDERR_FILENO, "usage: cd directory\n");
		return(1);
	}
	if (cmd[1] == NULL || ft_strequ("--", cmd[1]))
		path = get_env_value("HOME");
	else if (ft_strequ("-", cmd[1]))
	{
		print_dir = 1;
		path = get_env_value("OLDPWD");
	}
	else
		path = ft_strdup(cmd[1]);
	change_directory(path, print_dir);
	free(path);
	return (0);
}
