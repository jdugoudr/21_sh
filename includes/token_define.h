/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_define.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:37:26 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 19:28:15 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_DEFINE_H
# define TOKEN_DEFINE_H

# include "stdbool.h"

# define RESERVED	";&|<>()\'\""

# define SEMI_COL		0x1
# define AND_IF			0x2
# define OR_IF			0x4
# define PIPE_TOK		0x8
# define LESS_TOK		0x10
# define LESS_FD_TOK	0x20
# define DLESS_TOK		0x40
# define GREAT_TOK		0x80
# define GREAT_FD_TOK	0x100
# define DGREAT_TOK		0x200
# define DGREAT_FD_TOK	0x400
# define SUB_SHELL		0x800
# define QUOT_TOK		0x1000
# define DQUOT_TOK		0x2000
# define ASSIGN_TOK		0x4000
# define WORD_TOK		0x8000
# define NAME_TOK		0x10000
# define TYPE_END		0x20000

# define G_QUOT		QUOT_TOK | DQUOT_TOK
# define LEVEL_MIN	level_6
# define LEVEL_REDI	level_4
# define OUT_REDIR	(GREAT_TOK | DGREAT_TOK | GREAT_FD_TOK | DGREAT_FD_TOK)
# define IN_REDIR	(LESS_TOK | DLESS_TOK | LESS_FD_TOK)
# define FD_REDIR	(GREAT_FD_TOK | DGREAT_FD_TOK | LESS_FD_TOK)
# define IS_REDI	(OUT_REDIR | IN_REDIR)
# define L_IS_NAME	(WORD_TOK | IS_REDI)

# define ENA_FIRST	(NAME_TOK|WORD_TOK|SUB_SHELL|G_QUOT|TYPE_END|IS_REDI)

/*
** level_1 ';'
** level_2 '&&' '||'
** level_3 '|'
** level_4 '>' '>>' '<' '<<'
** level_5 '='
** level_6 WORD
*/

enum {level_7, level_6, level_5, level_4, level_3, level_2, level_1};

typedef struct		s_arg
{
	char			*arg;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_ast
{
	int				type;
	int				level_prior;
	char			*value;
	char			**arg_cmd;
	int				(*f_tok_next)(struct s_ast *, char **);
	int				(*f_exec)(struct s_ast *, struct s_ast *, int);
	struct s_ast	*next;
	struct s_ast	*prev;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*father;
	struct s_ast	*head_sub;
	struct s_ast	*ast_sub;
}					t_ast;

#endif
