/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 20:14:16 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/13 18:41:38 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "sh_error.h"
#include "libft.h"

/*
** Sets the value of an existing environment variable at index "ind" to "val".
*/

static int		set_env_value(size_t ind, char *key, char *val)
{
	free(g_shell->env[ind]);
	if ((g_shell->env[ind] = ft_strjoin(key, "=", 0)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	if ((g_shell->env[ind] = ft_strjoin(g_shell->env[ind], val, 1)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (0);
}

static int	check_var(char **cmd, int r, char **key, char **var)
{
	if (check_cmd_format(cmd, 1) == 1)
	{
		if ((*var = ft_strchr(cmd[1], '=')) == NULL)
			r = 1;
		else
		{
			(*var)[0] = '\0';
			*key = cmd[1];
			*var = *var + 1;
		}
	}
	else if (check_cmd_format(cmd, 2) == -1)
		r = 1;
	else
	{
		*key = cmd[1];
		*var = cmd[2];
	}
	if (r)
	{
		ft_dprintf(STDERR_FILENO, "usage: setenv key value\n");
		return (1);
	}
	return (0);
}

int			builtin_setenv(char **cmd)
{
	int		var_ind;
	char	*var;
	char	*key;

	if (cmd[1] == NULL)
	{
		builtin_env(cmd);
		return(0);
	}
	if (check_var(cmd, 0, &key, &var))
		return (1);
	if ((var_ind = get_env_ind(key)) == -1)
		return (1);
	else if (var_ind == -2)
		return (add_env_var(key, var));
	else
		return (set_env_value(var_ind, key, var));
}
