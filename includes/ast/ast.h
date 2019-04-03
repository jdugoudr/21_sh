/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:17:24 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/03 20:20:55 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "token_define.h"
# include "del_ast.h"

/*
** Define the levels priorities of all tokens
*/

//# define PRIO_ONE	(SEMI_COL)
//# define PRIO_TWO	(AND_IF | OR_IF)
//# define PRIO_THREE	(PIPE_TOK)
//# define PRIO_FOUR	(LESS_TOK | DLESS_TOK | GREAT_TOK | DGREAT_TOK)
//# define PRIO_FIVE	(ASSIGN_TOK)
//# define PRIO_SIX	(NAME_TOK | WORD_TOK | SUB_SHELL | QUOT_TOK)

typedef struct 	s_ast_reader
{
	t_ast		*node;
	int			out;
	int			in;
	char		**arg;
}				t_ast_reader;

int		create_ast(t_ast **root, t_ast *list_head);

#endif
