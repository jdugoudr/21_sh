/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell21.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:26:41 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/08 14:15:34 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL21_H
# define SHELL21_H

// # include <linux/limits.h>
# include <limits.h>
# include <term.h>
# include <termios.h>
# include <libft.h>
# include <stdio.h>	//delete
# define RET_KEY			0xA
# define ESC_KEY			0x1B
# define CTRL_A_KEY			0x1
# define CTRL_B_KEY			0x2
# define CTRL_K_KEY			0xB
# define CTRL_L_KEY			0xC
# define CTRL_P_KEY			0x10
# define CTRL_R_KEY			0x12
# define CTRL_U_KEY			0x15
# define CTRL_W_KEY			0x17
# define SPCE_KEY			0x20
# define BCKSPCE_KEY		0x7F
# define UP_KEY				0x415B1B
# define DOWN_KEY			0x425B1B
# define RIGHT_KEY			0x435B1B
# define LEFT_KEY			0x445B1B
# define DEL_KEY			0x7E335B1B
# define HOME_KEY			0x485B1B
# define END_KEY			0x465B1B
# define SHIFT_UP_KEY		0x41323B315B1B
# define SHIFT_DOWN_KEY		0X42323B315B1B
# define SHIFT_RIGHT_KEY	0X43323B315B1B
# define SHIFT_LEFT_KEY		0X44323B315B1B
# define READ_BUF_SZE		8
// # define COL_RES			"\033[00m"
// # define COL_CYAN			"\033[1;36m"
// # define COL_CYAN_BG		"\033[1;106m"
// # define COL_WHITE			"\033[1;107m"
/*
** Implementation of the command history using a doubly-linked list.
*/
struct					s_history
{
	char				name[ARG_MAX];
	struct s_history	*prev;
	struct s_history	*next;
};

/*
** Our Structure for line editing.
** cmd: 		the command being written.
** prompt:		the prompt string.
** quotes:		an integer representing the status of the open/closed quotes
**					0: no quotes that need to be closed.
**					1: a single quote that needs to be closed.
**					2: a double quote that needs to be closed.
*/
struct					s_editor
{
	char				cmd[ARG_MAX + 1];	//check arg_max
	char				cpy_buff[ARG_MAX + 1];
	char				prompt[PATH_MAX];
	int					quotes;
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

struct					s_shell
{
	char				**env;
	struct s_history	*hist;
	struct s_history	*hist_ptr;
};

typedef struct termios		t_termios;
typedef struct s_shell		t_shell;
typedef struct s_editor		t_editor;
typedef struct s_history	t_history;

/*
** We use a global variable for propre handling of signals.
*/
t_editor					*g_editor;

void					add_char(char c);
void					clear_string(char *str);
void					command_append(char *str, int rewrite_flag);
void					command_erase(void);
void					command_reset();
void					command_set(char *str, int rewrite_flag);
void					command_write(void);
void					detect_input(t_shell *shell);
void					display_prompt(void);
void					exec_cmd(t_shell *shell);	// delete
void					get_editor_dim(void);
void					init_signal_handlers(void);
void					move_cursor_home(void);
void					move_cursor_left(void);
void					move_cursor_right(void);
void					prompt_reset(void);
void					prompt_set(char *str);
int						quotes_balanced(void);
void					remove_char(void);
void					restore_default_conf(void);
void					set_terminfo(void);
void					start_search_mode(t_shell *shell);
void					start_visual_mode(void);
void					init_term(void);
int						tputs_char(int c);
void					write_in_visual(size_t start, size_t end);


/*
** Keypresses
*/

int						dispatch_keypress(t_shell *shell, unsigned long val);
void					keypress_backspace(void);
void					keypress_ctrl_b(size_t s, size_t e);
void					keypress_ctrl_k(size_t s, size_t e);
void					keypress_ctrl_l(void);
void					keypress_ctrl_p(void);
void					keypress_ctrl_u(void);
void					keypress_delete(void);
void					keypress_downarrow(t_shell *shell);
void					keypress_end(void);
void					keypress_home(void);
void					keypress_shift_down(void);
void					keypress_shift_left();
void					keypress_shift_right(void);
void					keypress_shift_up(void);
void					keypress_uparrow(t_shell *shell);

/*
** Utils
*/
void					add_env_var(char *key, char *val);
void					change_directory(char *path, int print_dir);
int						check_cmd_format(char **cmd, size_t param_num);
void					display_history(t_shell *shell);
void					free_editor(void);
void					free_string_array(char **array);
void					free_shell(t_shell *sh);
void					ft_exit(char *msg, int rstr, int free_fl, int ex_val);
size_t					get_count(char **t);
char					*get_env_value(char *key);
int						get_env_ind(char *env_var);
void					history_append(t_shell *shell, char *name);
void					set_last_history_entry(t_shell *shell);


/*
** Builtins
*/
void					builtin_cd(char **cmd);
void					builtin_echo(char **cmd);
void					builtin_env(void);
void					builtin_history(t_shell *shell);
void					builtin_setenv(char **cmd);
void					builtin_unsetenv(char **cmd);

#endif
