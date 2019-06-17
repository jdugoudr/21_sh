/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:17:24 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/17 14:23:42 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "token_define.h"
# include "shell21.h"

# define RUN_AFTER	(AND_IF | OR_IF)
# define NOT_DO_R	(LESS_TOK | DLESS_TOK | GREAT_TOK | DGREAT_TOK)

typedef struct	s_ast_reader
{
	t_ast		*node;
	int			out;
	int			in;
	char		**arg;
}				t_ast_reader;

int				create_ast(t_ast **root, t_ast *list_head);
t_ast			*create_token(void);
t_ast			*create_tok_el(char *str, t_ast *prev, t_ast *next);
void			del_token(t_ast **el);
void			del_arglst(t_arg **lst);
void			del_ast(t_ast **ast_head);

#endif
