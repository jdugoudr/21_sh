/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 19:02:11 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/10 19:07:37 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int	builtin_exit(char **cmd)
{
	(void)cmd;
	ft_exit(NULL, 1, 1, EXIT_SUCCESS);
	return (0);
}
