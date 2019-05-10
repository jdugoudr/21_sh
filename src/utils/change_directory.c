// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   change_directory.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/02/12 00:52:22 by mdaoud            #+#    #+#             */
// /*   Updated: 2019/03/28 13:44:33 by mdaoud           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "shell21.h"
// #include <limits.h>
// #include <limits.h>

// static void		set_oldpwd(char *val)
// {
// 	int			ind;
// 	char		*var;

// 	ind = get_env_ind("OLDPWD");
// 	free(g_editor->env[ind]);
// 	var = ft_strjoin("OLDPWD=", val, 0);
// 	g_editor->env[ind] = var;
// }

// static void		set_pwd(char *val)
// {
// 	int			ind;
// 	char		*var;
// 	char		curr_dir[PATH_MAX];

// 	if ((ind = get_env_ind("PWD")) == -1)
// 	{
// 		getcwd(curr_dir, PATH_MAX);
// 		add_env_var("PWD", curr_dir);
// 		return ;
// 	}
// 	free(g_editor->env[ind]);
// 	var = ft_strjoin("PWD=", val, 0);
// 	g_editor->env[ind] = var;
// }

// /*
// ** Changes the current working directory.
// ** Updates the environment variables "PWD" and "OLDPWD".
// ** In case of error, prints the appropriate error message.
// */

// void			change_directory(char *path, int print_dir)
// {
// 	char	old_dir[PATH_MAX];

// 	if (print_dir)
// 		ft_dprintf(g_editor->tty_fd, "%s\n", path);
// 	getcwd(old_dir, PATH_MAX);
// 	if (chdir(path) == -1)
// 	{
// 		if ((access(path, F_OK) == -1))
// 			ft_dprintf(g_editor->tty_fd, "cd: no such file or directory: %s\n", path);
// 		else if ((access(path, R_OK) == -1))
// 			ft_dprintf(g_editor->tty_fd, "cd: permission denied: %s\n", path);
// 		else
// 			ft_dprintf(g_editor->tty_fd, "cd: not a directory: %s\n", path);
// 		return ;
// 	}
// 	set_oldpwd(old_dir);
// 	set_pwd(path);
// }
