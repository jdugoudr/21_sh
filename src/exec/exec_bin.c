
#include "exec_cmd.h"
#include "sh_error.h"
#include "editor.h"
#include "ast.h"
#include <sys/types.h>
#include <sys/wait.h>//linux

/*
** We check on the env variable PATH if the binary file of the command exist.
** For that : We split PATH follow ':' and we create a compete path name
** /path/find/in/env/cmd_name.
**
** Info : You have to NOT free what it was allocated if you use execve.
** 		  If you do the program will stop with a double free issue.
*/

static void	free_exit(int r, t_ast *head)
{
	free_shell();
	free_editor();
	del_ast(&head);
	exit(r);
}

static int	exec_bin(char *path, char **arg, t_ast *head)
{
	pid_t	child;
	int		ret;

	ret = 0;
	if (access(path, X_OK))
	{
		ft_dprintf(STDERR_FILENO, NO_PERM, path);
		return (1);
	}
	child = fork();
	if (child == -1)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	else if (child == 0)
	{
		execve(path, arg, g_shell->env);
		ft_dprintf(STDERR_FILENO, "21sh: A problem appeared with execve.\n");
		free_exit(1, head);
	}
	else
		waitpid(child, &ret, 0);
	return (ret);
}

static char	*complete_path(char *path, char *name)
{
	char	*tmp;
	char	*com_path;

	if ((tmp = ft_strjoin(path, "/", 0)) == NULL)
		return (NULL);
	com_path = ft_strjoin(tmp, name, 0);
	free(tmp);
	return (com_path);
}

static int	check_path(t_ast *el, char **path_tab, t_ast *head)
{
	char	*com_path;
	int		ret;
	int		i;

	i = 0;
	while (path_tab[i])
	{
		if ((com_path = complete_path(path_tab[i], el->value)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, INTERN_ERR);
			return (1);
		}
		if (access(com_path, F_OK) == 0)
		{
			ret = exec_bin(com_path, el->arg_cmd, head);
			free(com_path);
			return (ret);
		}
		free(com_path);
		i++;
	}
	ft_dprintf(STDERR_FILENO, NO_CMD, el->value);
	return (1);
}

int			check_bin(t_ast *el, t_ast *head)
{
	int		ret;
	char	*path;
	char	**path_tab;

	ret = 0;
	if (access(el->value, F_OK) == 0)
		return (exec_bin(el->value, el->arg_cmd, head));
	if ((path = getenv("PATH")) != NULL)//getenv non autoriser, a remplace par le builtin
	{
		ret = 1;
		if ((path_tab = ft_strsplit(path, ':')) != NULL)
		{
			ret = check_path(el, path_tab, head);
			ft_tabstrdel(&path_tab, 0);
		}
		else
			ft_dprintf(STDERR_FILENO, INTERN_ERR);
	}
	return (ret);
}
