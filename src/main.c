/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:29:25 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/07 17:21:09 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "libft.h"
#include "shell21.h"

static void		init_env(t_shell *sh, char **environ)
{
	char	**env;
	int		count;

	count = 0;
	while (environ[count] != NULL)
		count++;
	if ((env = malloc(sizeof(char *) * (count + 1))) == NULL)
		ft_exit("malloc", 1, EXIT_FAILURE);
	env[count] = NULL;
	count = 0;
	while (environ[count] != NULL)
	{
		if ((env[count] = ft_strdup(environ[count])) == NULL)
		{
			while (count-- > 0)
				free(env[count]);
			free(env);
			ft_exit("malloc", 1, EXIT_FAILURE);
		}
		count++;
	}
	sh->env = env;
}

static t_shell		*init_shell(char **enviro)
{
	t_shell	*sh;

	if ((sh = malloc(sizeof(t_shell))) == NULL)
		ft_exit("malloc", 1, EXIT_FAILURE);
	sh->hist = NULL;
	sh->hist_ptr = NULL;
	if (enviro == NULL || *enviro == NULL)
		ft_exit("No environment specified.", 0, EXIT_FAILURE);
	else
		init_env(sh, enviro);
	ft_strcpy(g_editor->prompt, "$>> ");
	return (sh);
}

int				main(int argc, char **argv, char **enviro)
{
	t_shell	*shell;

	(void)argv;
	(void)argc;
	if ((g_editor = malloc(sizeof(t_editor))) == NULL)
		ft_exit("malloc", 0, EXIT_FAILURE);
	shell = init_shell(enviro);
	init_term();
	init_signal_handlers();
	while(1)
	{
		display_prompt();
		detect_input(shell);
	}
	return (0);
}