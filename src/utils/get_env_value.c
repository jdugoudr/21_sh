/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 22:04:26 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/20 15:30:06 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "libft.h"

char			*get_env_value(char *key)
{
	int		ind;
	char	*val;

	if ((ind = get_env_ind(key)) < 0)
		return (ft_strdup(""));
	val = ft_strchr(g_shell->env[ind], '=');
	return (ft_strdup(val + 1));
}
