/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:32:55 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/09 15:33:08 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	is_builtin(char *cmd)
{
	int			i;
	static char	**builtins;

	builtins = (char *[]){"", "echo", "cd", "pwd", "export",
		"unset", "env", "exit", NULL};
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	check_file_access(char *path, int mode)
{
	return (access(path, mode) == 0);
}

static char	*find_path(char **envp, char *str)
{
	char	*path;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (envp[i] != NULL)
	{
		if ((ft_strncmp(str, envp[i], len) == 0) && envp[i][len] == '=')
		{
			path = ft_strdup(envp[i] + len + 1);
			return (path);
		}
		++i;
	}
	return (NULL);
}

static char	*find_cmd_path(t_cmd *cmds)
{
	char	**temp;
	char	*res;
	char	*t;
	int		i;

	i = 0;
	if (!cmds->path)
		return (NULL);
	temp = ft_split(cmds->path, ':');
	while (temp[i] != NULL)
	{
		t = ft_strjoin(temp[i], "/");
		res = ft_strjoin(t, cmds->args[0]);
		free(t);
		if (access(res, X_OK) == 0)
			return (free_array(temp), res);
		free(res);
		i++;
	}
	free_array(temp);
	return (NULL);
}

char	*handle_path(t_cmd *cmds, char **envp)
{
	char	*res;

	if (cmds->args[0][0] == '/' ||
		(cmds->args[0][0] == '.' && cmds->args[0][1] == '/'))
	{
		if (access(cmds->args[0], X_OK) == 0)
			return (ft_strdup(cmds->args[0]));
		return (NULL);
	}
	cmds->path = find_path(envp, "PATH");
	if (!cmds->path)
		return (NULL);
	printf("%s\n\n\n", cmds->path);
	res = find_cmd_path(cmds);
	free(cmds->path);
	cmds->path = NULL;
	return (res);
}
