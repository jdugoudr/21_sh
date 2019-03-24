/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_define.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:37:26 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/24 17:57:15 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_DEFINE_H
# define TOKEN_DEFINE_H

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
# define CMD_TOK	0x0200
# define WORD_TOK	0x0400
# define ASSIGN_TOK	0x0800
# define QUOT_TOK	0x1000
# define DQUOT_TOK	0x2000

typedef struct		s_ast
{
	short			type;
	char			*value;
	char			**arg_cmd;
	int				(*f_tok_next)(struct s_ast);
	struct s_ast	*next;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

#endif
