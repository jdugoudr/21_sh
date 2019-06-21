/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_level.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:24:07 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/20 15:50:53 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "libft.h"
#include "sh_error.h"

static int		set_env_value(size_t ind, char *key, char *val)
{
	free(g_shell->env[ind]);
	if ((g_shell->env[ind] = ft_strjoin(key, "=", 0)) == NULL)
		return (1);
	if ((g_shell->env[ind] = ft_strjoin(g_shell->env[ind], val, 1)) == NULL)
		return (1);
	return (0);
}

void			init_shell_level(void)
{
	int		shlvl;
	int		ind;
	char	*tmp;

	ind = get_env_ind("SHLVL");
	if (ind < 0)
	{
		add_env_var("SHLVL", "1");
		return ;
	}
	tmp = get_env_value("SHLVL");
	shlvl = ft_atoi(tmp) + 1;
	free(tmp);
	if ((tmp = ft_itoa(shlvl)) == NULL || set_env_value(ind, "SHLVL", tmp))
	{
		free(tmp);
		ft_exit(INTERN_ERR, 1, 1, EXIT_FAILURE);
	}
	set_env_value(ind, "SHLVL", tmp);
	free(tmp);
}
