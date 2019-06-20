/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_ind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:57:09 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/20 15:24:59 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "sh_error.h"
#include "libft.h"

/*
** Returns the index of the environmet variable pointed by "env_var".
** Returns -2 if the variable doesn't exit.
** Returns -1 if a error appear
*/

int			get_env_ind(char *env_var)
{
	int		i;
	char	*find;

	i = 0;
	find = ft_strjoin(env_var, "=", 0);
	if (!find)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (-1);
	}
	while (g_shell->env[i] != NULL)
	{
		if (ft_strstr(g_shell->env[i], find) == g_shell->env[i])
		{
			free(find);
			return (i);
		}
		i++;
	}
	free(find);
	return (-2);
}
