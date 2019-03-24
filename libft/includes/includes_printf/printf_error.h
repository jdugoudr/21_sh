/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 13:05:50 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/24 13:06:22 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_ERROR_H
# define PRINTF_ERROR_H

# include "ft_printf.h"

# define ERR_NO_CONV		"Error, no valid conversion."
# define ERR_ADD_LIST		"Error, not possible to create a new list."
# define ERR_STR			"Error, not possible to create a new string."
# define ERR_FLAG			"Error, no valid flag or not possible to use it."
# define ERR_NOT_AVAIBLE	"Error, flag not avaible with this conversion."

void	printf_error(char *flag, char *to_free);

#endif
