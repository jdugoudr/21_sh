/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 10:17:12 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/20 10:00:37 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
# define EXEC_CMD_H

# include "token_define.h"
# include "libft.h"///////////////////////////
# include "shell21.h"

# define READ_END		0
# define WRITE_END		1
# define CLOSE_OUTPUT	"/dev/null"
# define HERE_DOC		"/tmp/heredoc_21"
# define NB_BUILT		5

typedef struct			s_built
{
	char				*name;
	int					(*func)(char **);
}						t_built;

typedef struct 			s_save_fd
{
	int					old_fd;
	int					save_fd;
//	int					file_open;
	struct s_save_fd	*next;
}						t_save_fd;

int						exec_semi_col(t_ast *el, t_ast *head);
int						exec_or_if(t_ast *el, t_ast *head);
int						exec_and_if(t_ast *el, t_ast *head);
int						exec_pipe(t_ast *el, t_ast *head);
int						exec_redirect(t_ast *el, t_ast *head);
int						exec_sub_shell(t_ast *el, t_ast *head);
int						exec_assign(t_ast *el, t_ast *head);
int						exec_word(t_ast *el, t_ast *head);
int						exec_dless_fd(t_ast *el, t_ast *head);

int						check_bin(t_ast *el, t_ast *head);
int						find_and_exec_redirect(t_ast *el, t_save_fd **fd_lst);

char					**lsttotab(t_arg *lst);

int						exec_in_redir(t_ast *el, t_save_fd **fd_lst, int open_flag, int fd_in);
int						exec_out_redir(t_ast *el, t_save_fd **fd_lst, int open_flag, int fd_in);

void					del_saved_fd(t_save_fd **fd_lst);
int						is_saved(t_save_fd *lst, int fd);
t_save_fd				*add_value(t_save_fd *fd_lst, int to_save, int saved);
int						save_fd(t_save_fd **fd_lst, int fd);
int				 		check_left_fd(t_save_fd **fd_lst, int fd, int tok_red);
int 					check_right_fd(t_save_fd *fd_lst, int fd, int tok_red);

int						get_fd(char *name_file, int open_flag, int *new_fd, t_save_fd **fd_lst);
int						file_descriptor(char *value, int *new_fd);
void print_fd(t_save_fd *el);////a supprimer !!!
#endif
