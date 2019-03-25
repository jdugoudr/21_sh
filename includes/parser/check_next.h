/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_next.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:10:09 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/25 19:27:13 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_NEXT_H
# define CHECK_NEXT_H

# include "token_define.h"

/*
** This the token which CAN NOT appear after the token AFTER_[TOKEN]
*/

# define AFTER_ASS	(WORD_TOK | NAME_TOK | ASSIGN_TOK | QUOT_TOK)
# define AFTER_WORD	(SUB_SHELL | NAME_TOK | ASSIGN_TOK)

/*
** This is the token which CAN appear after the token AFTER_[TOKEN]
*/

# define AFTER_ANOR	(NAME_TOK | WORD_TOK | SUB_SHELL)
# define AFTER_NAME	(ASSIGN_TOK)
# define AFTER_PIPE	(WORD_TOK | SUB_SHELL)

/*
** Check next token functions
*/

int	check_for_assign(t_ast *next);
int	check_for_word(t_ast *next);
int	check_for_name(t_ast *next);
int	check_for_and_or(t_ast *next);
int	check_for_pipe(t_ast *next);
int	check_for_quot(t_ast *next);

#endif
