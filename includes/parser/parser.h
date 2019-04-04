/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:12:03 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/04 13:00:27 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token_define.h"

int		parser(char *line);
t_ast	*sort_redirect(t_ast *start, t_ast *end);
t_ast	*create_arg(t_ast *start, t_ast *end);

#endif
