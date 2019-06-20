/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell21.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:26:41 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/20 15:32:48 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL21_H
# define SHELL21_H

# include <limits.h>
# include <term.h>
# include <termios.h>
# include <stdlib.h>

/*
** Implementation of the command history using a doubly-linked list.
*/
struct					s_history
{
	char				name[ARG_MAX];
	struct s_history	*prev;
	struct s_history	*next;
};

struct					s_shell
{
	char				**env;
	struct s_history	*hist;
	struct s_history	*hist_ptr;
};

typedef struct s_shell		t_shell;
typedef struct s_history	t_history;

/*
** We use a global variable for propre handling of signals.
*/
t_shell					*g_shell;

/*
** Utils
*/
int						add_env_var(char *key, char *val);
void					change_directory(char *path, int print_dir);
int						check_cmd_format(char **cmd, size_t param_num);
void					display_history(void);
void					free_shell(void);
void					free_string_array(char **array);
void					ft_exit(char *msg, int rstr, int free_fl, int ex_val);
size_t					get_env_var_count(char **t);
char					*get_env_value(char *key);
int						get_env_ind(char *env_var);
void					history_append(char *name);
void					init_shell_level(void);
void					set_last_history_entry(void);

/*
** Builtins
*/
int						builtin_cd(char **cmd);
int						builtin_echo(char **cmd);
int						builtin_env(char **cmd);
int						builtin_history(char **cmd);
int						builtin_setenv(char **cmd);
int						builtin_unsetenv(char **cmd);
int						builtin_exit(char **cmd);

#endif
