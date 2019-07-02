/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:14:14 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/26 18:10:30 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "libft.h"
#include "editor.h"
#include "sh_error.h"

/*
** Removes the environmet variable at index "ind".
** Reallocs the shell's environment array.
*/

static int	remove_env_var(int ind)
{
	char	**new_env;
	int		count;
	size_t	i;

	count = get_env_var_count(g_shell->env);
	if ((new_env = malloc(sizeof(char *) * (count))) == NULL)
		return (1);
	i = 0;
	count = 0;
	while (g_shell->env[count] != NULL)
	{
		if (count == ind)
		{
			free(g_shell->env[count]);
			count++;
			continue ;
		}
		new_env[i++] = g_shell->env[count++];
	}
	new_env[i] = NULL;
	free(g_shell->env);
	g_shell->env = new_env;
	return (0);
}

/*
** Checks that the command is well formatted.
** Removes the environment variable specified in cmd if it exists.
** Does nothing if the string given does not exist.
*/

int			builtin_unsetenv(char **cmd)
{
	int		ind;
	int		retval;

	if (check_cmd_format(cmd, 1) == -1)
	{
		write(STDERR_FILENO, "usage: unsetenv variable_name\n", 30);
		return (0);
	}
	if ((ind = get_env_ind(cmd[1])) < 0)
		return (0);
	retval = remove_env_var(ind);
	if (retval)
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
	return (retval);
}
