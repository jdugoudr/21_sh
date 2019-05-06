// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   builtin_echo.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/02/10 02:48:47 by mdaoud            #+#    #+#             */
// /*   Updated: 2019/03/27 18:38:04 by mdaoud           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "shell21.h"

// /*
// ** Handles the echo command when the "-n" option is specified.
// ** -n: do not output the trailing newline character.
// */

// static void			echo_with_no_newline(char **cmd)
// {
// 	size_t		i;

// 	if (cmd[2] == NULL)
// 	{
// 		free_string_array(cmd);
// 		return ;
// 	}
// 	i = 2;
// 	while (cmd[i] != NULL)
// 	{
// 		ft_printf("%s", cmd[i]);
// 		if (cmd[i + 1] != NULL)
// 			ft_printf(" ");
// 		i++;
// 	}
// 	free_string_array(cmd);
// 	return ;
// }

// void				builtin_echo(char **cmd)
// {
// 	size_t	i;

// 	if (cmd[1] == NULL)
// 	{
// 		ft_printf("\n");
// 		free_string_array(cmd);
// 		return ;
// 	}
// 	else if (ft_strequ("-n", cmd[1]))
// 		return (echo_with_no_newline(cmd));
// 	i = 1;
// 	while (cmd[i] != NULL)
// 	{
// 		ft_printf("%s", cmd[i]);
// 		if (cmd[i + 1] != NULL)
// 			ft_printf(" ");
// 		i++;
// 	}
// 	ft_printf("\n");
// 	free_string_array(cmd);
// 	return ;
// }
