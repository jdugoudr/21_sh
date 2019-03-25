/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:33:09 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/25 17:26:08 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token_define.h"
# include <stdbool.h>

t_ast	*next_token(char **line, bool *is_name);

t_ast	*and_find(char **line, t_ast *tok/*, bool *is_name*/);
t_ast	*or_find(char **line, t_ast *tok/*, bool *is_name*/);
t_ast	*word_find(char **line, t_ast *tok, bool *is_name);
t_ast	*quot_find(char **line, t_ast *tok, char c);

void	consume(char **line);

#endif
