/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_subst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:22:34 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/20 15:17:22 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "sh_error.h"
#include "libft.h"

/*
** Here we extract a variable name from string ($VAR1$VAR2),
** looking for it in env, and replace it if exist. If it not, the variable is
** remove and ignored
*/

static int	replace_in(char **str, char *tmp, int i, int j)
{
	char	*new;
	size_t	len;
	size_t	len_add;

	if (!tmp)
		len_add = 0;
	else
		len_add = ft_strlen(tmp);
	len = ft_strlen(*str) - j + len_add;
	if ((new = ft_strnew(len)) == NULL)
	{
		free(*str);
		*str = NULL;
		return (-1);
	}
	(*str)[i] = '\0';
	ft_strcat(new, *str);
	if (tmp)
		ft_strcat(new, tmp);
	ft_strcat(new, (*str) + i + j);
	free(*str);
	*str = new;
	return (i + len_add);
}

static char	*replace_each(int *i, char *str)
{
	int		j;
	char	c;
	char	*tmp;

	j = *i + 1;
	while (str[j] && ft_isalnum(str[j]))
		j++;
	c = str[j];
	str[j] = '\0';
	if ((tmp = get_env_value(str + *i + 1)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		free(str);
		return (NULL);
	}
	str[j] = c;
	if ((*i = replace_in(&str, tmp, *i, j - *i)) < 0)
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
	free(tmp);
	return (str);
}

static char	*spec_char(int *i, char *str, char c, int ret)
{
	int		r;
	char	*tmp;

	r = 0;
	if (c == '$')
		r = getpid();
	else if (c == '?')
		r = ret;
	tmp = ft_itoa(r);
	if (tmp == NULL || (*i = replace_in(&str, tmp, *i, 2)) < 0)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		free(str);
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (str);
}

char		*env_subst(char *str, int ret)
{
	int		i;

	i = 0;
	if (!str)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (NULL);
	}
	while (str && str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		if (str[i])
		{
			if (str[i + 1] == '$' || str[i + 1] == '?')
				str = spec_char(&i, str, str[i + 1], ret);
			else if (ft_isalnum(str[i + 1]))
				str = replace_each(&i, str);
			else
				i++;
		}
	}
	return (str);
}
