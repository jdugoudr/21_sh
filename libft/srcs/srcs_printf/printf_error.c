/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 13:07:16 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/24 13:07:18 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_error.h"

void	printf_error(char *flag, char *to_free)
{
	ft_putendl(flag);
	free(to_free);
	exit(EXIT_FAILURE);
}
