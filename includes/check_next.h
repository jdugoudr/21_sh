/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_next.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:10:09 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/28 17:24:11 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_NEXT_H
# define CHECK_NEXT_H

# include "token_define.h"

/*
** This the token which CAN NOT appear after the token AFTER_[TOKEN]
*/

# define AFTER_ASS		(WORD_TOK | NAME_TOK | G_QUOT | SUB_SHELL | ASSIGN_TOK)
# define AFTER_WORD		(SUB_SHELL | NAME_TOK | ASSIGN_TOK)
# define AFTER_SUB		(WORD_TOK | NAME_TOK | G_QUOT | SUB_SHELL | ASSIGN_TOK)
# define AFTER_SEMI		(ASSIGN_TOK | SEMI_COL)

/*
** This is the token which CAN appear after the token AFTER_[TOKEN]
*/

# define AFTER_ANOR		(NAME_TOK | WORD_TOK | SUB_SHELL | G_QUOT | IS_REDI)
# define AFTER_NAME		(ASSIGN_TOK)
# define AFTER_PIPE		(WORD_TOK | SUB_SHELL | G_QUOT | NAME_TOK | IS_REDI)
# define AFTER_REDIR_FD	(WORD_TOK | G_QUOT)
# define AFTER_DLESS	(WORD_TOK | G_QUOT)
# define AFTER_LESS		(WORD_TOK | G_QUOT)
# define AFTER_DGREAT	(WORD_TOK | G_QUOT)
# define AFTER_GREAT	(WORD_TOK | G_QUOT)

/*
** Check next token functions
*/

int	check_for_assign(t_ast *next, char **line);
int	check_for_word(t_ast *next, char **line);
int	check_for_name(t_ast *next, char **line);
int	check_for_and_or(t_ast *next, char **line);
int	check_for_pipe(t_ast *next, char **line);
int	check_for_semi(t_ast *next, char **line);
int	check_for_dless(t_ast *next, char **line);
int	check_for_less(t_ast *next, char **line);
int	check_for_dgreat(t_ast *next, char **line);
int	check_for_great(t_ast *next, char **line);
int	check_for_sub(t_ast *next, char **line);
int	check_for_redir_fd(t_ast *next, char **line);

#endif
