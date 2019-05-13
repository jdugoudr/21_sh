/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_ind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:57:09 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/13 17:48:54 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "sh_error.h"
#include "libft.h"

/*
** Returns the index of the environmet variable pointed by "env_var".
** Returns -1 if the variable doesn't exit.
*/

int			get_env_ind(char *env_var, int *r)
{
	int		i;
	char	*find;

	i = 0;
	find = ft_strjoin(env_var, "=", 0);
	if (!find)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	while (g_shell->env[i] != NULL)
	{
		if (ft_strstr(g_shell->env[i], find) == g_shell->env[i])
		{
			free(find);
			*r = i;
			return (0);
		}
		i++;
	}
	free(find);
	*r = -1;
	return (0);
}
