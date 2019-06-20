/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 03:30:49 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/20 15:11:56 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "sh_error.h"
#include "libft.h"

/*
** Reallocates the environment array to add a new variable.
** Adds the string key=value to the new list of the environment variables.
*/

int			add_env_var(char *key, char *val)
{
	size_t	count;
	char	**new_env;

	count = get_env_var_count(g_shell->env);
	if ((new_env = malloc(sizeof(char *) * (count + 2))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	new_env[count + 1] = NULL;
	count = 0;
	while (g_shell->env[count] != NULL)
	{
		new_env[count] = g_shell->env[count];
		count++;
	}
	free(g_shell->env);
	if ((new_env[count] = ft_strjoin(key, "=", 0)) == NULL
		|| (new_env[count] = ft_strjoin(new_env[count], val, 1)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	g_shell->env = new_env;
	return (0);
}
