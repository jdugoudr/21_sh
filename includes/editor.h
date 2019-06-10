/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:26:41 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/10 19:34:40 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include <limits.h>
# include <term.h>
# include <termios.h>
# include <stdlib.h>
# define BALANCED			0
# define SINGLE_Q			1
# define DOUBLE_Q			2
# define PARANTH			4
# define RED				"\033[1;31m"
# define RES_COL			"\033[0m"
# define GREEN				"\033[1;32m"

/*
** Our Structure for line editing.
** cmd: 		the command being written.
** prompt:		the prompt string.
** quotes:		an integer representing the status of the open/closed quotes
**					0: no quotes that need to be closed.
**					1: a single quote that needs to be closed.
**					2: a double quote that needs to be closed.
**					4: a parantheses that needs to be closed.
*/
struct					s_editor
{
	char				cmd[ARG_MAX + 1];
	char				cpy_buff[ARG_MAX + 1];
	char				prompt[PATH_MAX];
	int					quotes;
	int					flag_sigint;
	int					open_subsh;
	int					tty_fd;
	size_t				cur_pos;
	size_t				cmd_sze;
	size_t				line;
	size_t				col;
	size_t				max_line;
	size_t				offset;
	size_t				win_width;
	size_t				win_height;
	struct termios		*term;
	struct termios		*oldterm;
};

typedef struct termios		t_termios;
typedef struct s_editor		t_editor;

/*
** We use a global variable for propre handling of signals.
*/
t_editor				*g_editor;

void					add_char(char c);
void					clear_string(char *str);
void					command_append(char *str, int rewrite_flag);
void					command_erase(void);
void					command_reset(void);
void					command_set(char *str, int rewrite_flag);
void					command_write(void);
void					continue_until_balanced(void);
void					detect_input(void);
int						dispatch_heredoc_key(unsigned long touch);
int						expression_balanced(void);
void					free_editor(void);
void					get_editor_dim(void);
void					handler_sigint_process(int signo);
void					init_term(void);
int						is_empty_cmd(void);
void					init_signal_handlers(void);
void					move_cursor_home(void);
void					move_cursor_left(void);
void					move_cursor_right(void);
void					prompt_display(void);
void					prompt_reset(void);
void					prompt_set(char *str);
int						quotes_balanced(void);
long					reader(void);
void					remove_char(void);
void					remove_subshell_newline(void);
void					restore_default_conf(void);
void					set_terminfo(void);
char					*start_heredoc_mode(char *end_here);
void					start_search_mode(void);
void					start_visual_mode(void);
int						tputs_char(int c);
void					write_in_visual(size_t start, size_t end);

#endif
