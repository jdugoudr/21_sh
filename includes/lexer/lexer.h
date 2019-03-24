/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:33:09 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/24 17:01:50 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "token_define.h"

t_ast	*next_token(char **line);

t_ast	*and_find(char **line, t_ast *tok);
t_ast	*or_find(char **line, t_ast *tok);
t_ast	*word_find(char **line, t_ast *tok);
void	consume(char **line);

#endif
