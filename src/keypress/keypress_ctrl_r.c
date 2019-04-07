/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_ctrl_r.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:44:51 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/02 11:12:43 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static int		get_search_entry(char *str, t_shell *shell, int fresh_search)
{
	t_history	*tmp;

	if (shell->hist == NULL || ft_strequ(str, ""))
		return (0);
	if (fresh_search || shell->hist_ptr == NULL)
		set_last_history_entry(shell);
	else if (shell->hist_ptr != NULL && shell->hist_ptr != NULL)
	{
		tmp = shell->hist_ptr;
		shell->hist_ptr = shell->hist_ptr->prev;
	}
	while (shell->hist_ptr != NULL)
	{
		if (ft_strstr(shell->hist_ptr->name, str) != NULL)
			return (1);
		shell->hist_ptr = shell->hist_ptr->prev;
	}
	if (!fresh_search && ft_strstr(tmp->name, str) != NULL)
	{
		shell->hist_ptr = tmp;
		return (1);
	}
	return (0);
}

static int		process_keypress(unsigned int val)
{
	if (val >= ' ' && val <= '~')
	{
		add_char(val);
		return (1);
	}
	else if (val == BCKSPCE_KEY)
	{
		keypress_backspace();
		return (1);
	}
	else if (val == CTRL_R_KEY)
		return (0);
	else
		return (2);
}

static void		exit_search_mode(t_shell *shell, char *prmpt)
{
	set_prompt(prmpt);
	if (shell->hist_ptr == NULL)
		command_reset();
	else
		command_set(shell->hist_ptr->name, 0);
	shell->hist_ptr = NULL;
	rewrite_lines();
	return ;
}

void			keypress_ctrl_r(t_shell *shell)
{
	char	prmpt_backup[PATH_MAX];
	char	search_str[ARG_MAX];
	int		fresh_search;
	char	buf[8];

	ft_strcpy(prmpt_backup, g_editor->prompt);
	command_erase();
	command_reset();
	set_prompt("(search: `");
	clear_buf(buf, 8);
	rewrite_lines();
	fresh_search = 1;
	while (read(STDIN_FILENO, buf, 7))
	{
		fresh_search = process_keypress(*(unsigned int *)buf);
		if (fresh_search == 2)
			return (exit_search_mode(shell, prmpt_backup));
		ft_strcpy(search_str, g_editor->cmd);
		command_append("': ", 1);
		if (get_search_entry(search_str, shell, fresh_search))
			command_append(shell->hist_ptr->name, 1);
		command_set(search_str, 0);
		clear_buf(buf, 8);
	}
}