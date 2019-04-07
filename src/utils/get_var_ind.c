// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   get_var_ind.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/02/09 21:57:09 by mdaoud            #+#    #+#             */
// /*   Updated: 2019/03/28 13:44:33 by mdaoud           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "shell21.h"

// /*
// ** Returns the index of the environmet variable pointed by "env_var".
// ** Returns -1 if the variable doesn't exit.
// */

// int			get_env_ind(char *env_var)
// {
// 	int		i;
// 	char	*find;

// 	i = 0;
// 	find = ft_strjoin(env_var, "=", 0);
// 	while (g_editor->env[i] != NULL)
// 	{
// 		if (ft_strstr(g_editor->env[i], find) == g_editor->env[i])
// 		{
// 			free(find);
// 			return (i);
// 		}
// 		i++;
// 	}
// 	free(find);
// 	return (-1);
// }
