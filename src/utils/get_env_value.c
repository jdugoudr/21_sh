// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   get_env_value.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/02/09 22:04:26 by mdaoud            #+#    #+#             */
// /*   Updated: 2019/03/28 13:44:33 by mdaoud           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "shell21.h"

// char			*get_env_value(char *key)
// {
// 	int		ind;
// 	char	*val;

// 	if ((ind = get_env_ind(key)) == -1)
// 		return (ft_strdup(""));
// 	val = ft_strchr(g_editor->env[ind], '=');
// 	return (ft_strdup(val + 1));
// }
