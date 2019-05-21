/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 22:04:26 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/21 10:45:42 by jdugoudr         ###   ########.fr       */
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
