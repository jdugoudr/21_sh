/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 10:17:12 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/17 14:24:53 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
# define EXEC_CMD_H

# include "token_define.h"
# include "shell21.h"

# define READ_END		0
# define WRITE_END		1
# define HERE_DOC		"/tmp/heredoc_21"
# define NB_BUILT		7

typedef struct			s_blt
{
	char				*name;
	int					(*func)(char **cmd);
}						t_blt;

typedef struct			s_cmd
{
	t_ast				*start;
	t_ast				*el;
	t_ast				*cmd;
}						t_cmd;

typedef struct			s_fd
{
	int					old_fd;
	int					save_fd;
	struct s_fd			*next;
}						t_fd;

int						run_ast(t_ast *root, t_ast *head, int ret);

int						expansion_tok(t_ast *el, t_ast **end, int ret);
char					*env_subst(char *str, int ret);
int						convert_tild(char **str);
int						convert_var(char ***tmp, t_ast **new,
										t_ast *el, int ret);

int						exec_semi_col(t_ast *el, t_ast *head, int ret);
int						exec_or_if(t_ast *el, t_ast *head, int ret);
int						exec_and_if(t_ast *el, t_ast *head, int ret);
int						exec_pipe(t_ast *el, t_ast *head, int ret);
int						exec_sub_shell(t_ast *el, t_ast *head, int ret);
int						exec_assign(t_ast *el, t_ast *head, int ret);
int						exec_word(t_ast *el, t_ast *head, int ret);
int						exec_dless_fd(t_ast *el, t_ast *head, int ret);

int						check_bin(t_ast *el);
int						find_and_exec_redirect(t_ast *el, t_fd **fd_lst);
int						free_reset_fd(t_fd **fd_lst, t_ast *head, int ret);

int						exec_in_redir(t_ast *el, t_fd **fd_lst,
							int open_flag, int fd_in);
int						exec_out_redir(t_ast *el, t_fd **fd_lst,
							int open_flag, int fd_in);
void					reset_term(t_ast *head, int ret);
void					del_saved_fd(t_fd **fd_lst);
int						is_saved(t_fd *lst, int fd);
t_fd					*add_value(t_fd *fd_lst, int to_save, int saved);
int						save_fd(t_fd **fd_lst, int fd);

int						check_left_fd(t_fd **fd_lst, int fd, int tok_red);
int						check_right_fd(t_fd *fd_lst, int fd, int tok_red);
int						get_fd(char *name_file, int open_flag, int *new_fd,
							t_fd **fd_lst);
int						file_descriptor(char *value, int *new_fd);

int						create_arg(t_cmd w_ast, int nb_arg);

#endif
