/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 20:14:16 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/28 15:46:51 by mdaoud           ###   ########.fr       */
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
		write(STDERR_FILENO, INTERN_ERR, ft_strlen(INTERN_ERR));
		return (1);
	}
	if ((g_shell->env[ind] = ft_strjoin(g_shell->env[ind], val, 1)) == NULL)
	{
		write(STDERR_FILENO, INTERN_ERR, ft_strlen(INTERN_ERR));
		return (1);
	}
	return (0);
}

int				builtin_setenv(char **cmd)
{
	int		var_ind;
	char	*val;
	char	*key;

	if (check_cmd_format(cmd, 2) == -1)
	{
		write(STDERR_FILENO, "usage: setenv key value\n", 24);
		return (1);
	}
	key = cmd[1];
	val = cmd[2];
	if ((var_ind = get_env_ind(key)) == -1)
		return (1);
	else if (var_ind == -2)
		return (add_env_var(key, val));
	else
		return (set_env_value(var_ind, key, val));
}
