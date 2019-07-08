/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_level.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:24:07 by mdaoud            #+#    #+#             */
/*   Updated: 2019/07/08 10:38:32 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "libft.h"
#include "sh_error.h"

static int		set_env_value(size_t ind, char *key, char *val)
{
	char	*tmp1;
	char	*tmp2;
	char	*backup;

	(void)val;
	backup = g_shell->env[ind];
	if ((tmp1 = ft_strjoin(key, "=", 0)) == NULL)
		return (1);
	if ((tmp2 = ft_strjoin(tmp1, val, 0)) == NULL)
	{
		free(tmp1);
		return (1);
	}
	g_shell->env[ind] = tmp2;
	free(tmp1);
	free(backup);
	return (0);
}

static void		raise_shell_level(int ind, char *tmp)
{
	int		shlvl;

	shlvl = ft_atoi(tmp) + 1;
	free(tmp);
	if ((tmp = ft_itoa(shlvl)) == NULL || set_env_value(ind, "SHLVL", tmp))
	{
		free(tmp);
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return ;
	}
	set_env_value(ind, "SHLVL", tmp);
	free(tmp);
}

void			init_shell_level(void)
{
	int		ind;
	char	*tmp;

	ind = get_env_ind("SHLVL");
	if (ind == -2)
	{
		if (add_env_var("SHLVL", "1"))
			ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return ;
	}
	else if (ind == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return ;
	}
	if ((tmp = get_env_value("SHLVL")) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "malloc: could not get SHLVL variable\n");
		return ;
	}
	raise_shell_level(ind, tmp);
}
