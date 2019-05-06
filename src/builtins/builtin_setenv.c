// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   builtin_setenv.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/02/08 20:14:16 by mdaoud            #+#    #+#             */
// /*   Updated: 2019/03/28 18:23:05 by mdaoud           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "shell21.h"

// /*
// ** Sets the value of an existing environment variable at index "ind" to "val".
// */

// static void		set_env_value(size_t ind, char *key, char *val)
// {
// 	free(g_editor->env[ind]);
// 	g_editor->env[ind] = ft_strjoin(key, "=", 0);
// 	g_editor->env[ind] = ft_strjoin(g_editor->env[ind], val, 1);
// }

// void			builtin_setenv(char **cmd)
// {
// 	int		var_ind;

// 	if (check_cmd_format(cmd, 0) == -1 && check_cmd_format(cmd, 2) == -1)
// 	{
// 		ft_printf("usage: setenv key value\n");
// 		return ;
// 	}
// 	if (cmd[1] == NULL)
// 	{
// 		builtin_env();
// 		return ;
// 	}
// 	var_ind = get_env_ind(cmd[1]);
// 	if (var_ind == -1)
// 		add_env_var(cmd[1], cmd[2]);
// 	else
// 		set_env_value(var_ind, cmd[1], cmd[2]);
// }
