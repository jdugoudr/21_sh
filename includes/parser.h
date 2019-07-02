/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:12:03 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/17 14:24:30 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token_define.h"
# include "shell21.h"

int		check_token(t_ast **token_head, t_ast *tok, char **line);
int		loop_tok(t_ast **token_head, char **line);
t_ast	*look_arg(t_ast *start);

int		parser(char *line);
t_ast	*sort_arg(t_ast *start, t_ast *end);

#endif
