/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_search_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:11:32 by mdaoud            #+#    #+#             */
/*   Updated: 2019/07/01 18:45:05 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "shell21.h"
#include "keypress.h"
#include "libft.h"

static int		get_search_entry(char *str, int fresh_search)
{
	t_history	*tmp;

	if (g_shell->hist == NULL || ft_strequ(str, ""))
		return (0);
	if (fresh_search || g_shell->hist_ptr == NULL)
		set_last_history_entry();
	else if (g_shell->hist_ptr != NULL && g_shell->hist_ptr != NULL)
	{
		tmp = g_shell->hist_ptr;
		g_shell->hist_ptr = g_shell->hist_ptr->prev;
	}
	while (g_shell->hist_ptr != NULL)
	{
		if (ft_strstr(g_shell->hist_ptr->name, str) != NULL)
			return (1);
		g_shell->hist_ptr = g_shell->hist_ptr->prev;
	}
	if (!fresh_search && ft_strstr(tmp->name, str) != NULL)
	{
		g_shell->hist_ptr = tmp;
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

static void		exit_search_mode(char *prmpt, char *search_str)
{
	prompt_set(prmpt);
	if (g_shell->hist_ptr == NULL || search_str[0] == '\0')
		command_reset();
	else
		command_set(g_shell->hist_ptr->name, 0);
	g_shell->hist_ptr = NULL;
	command_erase();
	command_write();
	return ;
}

static void		init_search(char prmpt[], char srch[], char tmp[])
{
	ft_strcpy(prmpt, g_editor->prompt);
	command_erase();
	command_reset();
	prompt_set("(search: `");
	ft_memset(srch, '\0', ARG_MAX);
	ft_memset(tmp, '\0', ARG_MAX);
	command_write();
}

void			start_search_mode(void)
{
	char			prmpt_backup[PATH_MAX];
	char			tmp[ARG_MAX];
	char			search_str[ARG_MAX];
	int				fresh_search;
	unsigned long	buf;

	init_search(prmpt_backup, search_str, tmp);
	fresh_search = 1;
	while ((buf = reader()))
	{
		fresh_search = process_keypress(buf);
		clear_string(tmp);
		if (fresh_search == 2)
			return (exit_search_mode(prmpt_backup, search_str));
		ft_strcpy(search_str, g_editor->cmd);
		command_append("': ", 1);
		if (get_search_entry(search_str, fresh_search))
			command_append(g_shell->hist_ptr->name, 1);
		ft_strcpy(tmp, g_editor->cmd);
		command_set(search_str, 0);
	}
}
