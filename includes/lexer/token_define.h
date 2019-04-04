/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_define.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:37:26 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/04 10:06:46 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_DEFINE_H
# define TOKEN_DEFINE_H

# include "stdbool.h"

# define RESERVED	";&|<>()\'\""

# define TYPE_END	0x0000
# define SEMI_COL	0x0001
# define AND_IF		0x0002
# define OR_IF		0x0004
# define PIPE_TOK	0x0008
# define LESS_TOK	0x0010
# define DLESS_TOK	0x0020
# define GREAT_TOK	0x0040
# define DGREAT_TOK	0x0080
# define SUB_SHELL	0x0100
# define QUOT_TOK	0x0200
# define ASSIGN_TOK	0x0400
# define WORD_TOK	0x0800
# define NAME_TOK	0x1000

# define LEVEL_MIN	level_6

# define ENA_FIRST	(NAME_TOK | WORD_TOK | SUB_SHELL | QUOT_TOK)

/*
** level_1 ';'
** level_2 '&&' '||'
** level_3 '|'
** level_4 '>' '>>' '<' '<<'
** level_5 '=' 
** level_6 WORD
*/

enum {level_6 = 1, level_5, level_4, level_3, level_2, level_1};

typedef struct		s_ast
{
	unsigned short	type;
	int				level_prior;
	char			*value;
	char			**arg_cmd;
	int				(*f_tok_next)(struct s_ast *);
	struct s_ast	*next;
	struct s_ast	*prev;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

#endif
