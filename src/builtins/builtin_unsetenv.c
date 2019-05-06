// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/02/09 20:14:14 by mdaoud            #+#    #+#             */
// /*   Updated: 2019/03/28 13:44:33 by mdaoud           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "shell21.h"

// /*
// ** Removes the environmet variable at index "ind".
// ** Reallocs the shell's environment array.
// */

// static void			remove_env_var(int ind)
// {
// 	char	**new_env;
// 	int		count;
// 	size_t	i;

// 	count = get_count(g_editor->env);
// 	if ((new_env = malloc(sizeof(char *) * (count))) == NULL)
// 		exit(1);
// 	i = 0;
// 	count = 0;
// 	while (g_editor->env[count] != NULL)
// 	{
// 		if (count == ind)
// 		{
// 			free(g_editor->env[count]);
// 			count++;
// 			continue ;
// 		}
// 		new_env[i++] = g_editor->env[count++];
// 	}
// 	new_env[i] = NULL;
// 	free(g_editor->env);
// 	g_editor->env = new_env;
// }

// /*
// ** Checks that the command is well formatted.
// ** Removes the environment variable specified in cmd if it exists.
// ** Does nothing if the string given does not exist.
// */

// void				builtin_unsetenv(char **cmd)
// {
// 	int		ind;

// 	if (check_cmd_format(cmd, 1) == -1)
// 	{
// 		ft_printf("usage: unsetenv variable_name\n");
// 		return ;
// 	}
// 	if ((ind = get_env_ind(cmd[1])) == -1)
// 		return ;
// 	remove_env_var(ind);
// }
