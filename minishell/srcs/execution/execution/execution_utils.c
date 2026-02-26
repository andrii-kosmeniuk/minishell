/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:32:55 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/26 22:25:47 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static char	*find_cmd_path(t_cmd *cmds, char *path_value)
{
	char	**temp;
	char	*res;
	char	*t;
	int		i;

	i = 0;
	if (!path_value)
		return (NULL);
	temp = ft_split(path_value, ':');
	if (!temp)
		return (NULL);
	while (temp[i])
	{
		t = ft_strjoin(temp[i], "/");
		res = ft_strjoin(t, cmds->args[0]);
		free(t);
		if (!res)
			return (free_array(temp), NULL);
		if (access(res, X_OK) == 0)
			return (free_array(temp), res);
		free(res);
		i++;
	}
	free_array(temp);
	return (NULL);
}

static bool	path_lookup_allowed(char *path_value)
{
	if (!path_value || path_value[0] == '\0')
		return (false);
	return (true);
}

static char	*resolve_local_path(t_cmd *cmds)
{
	char	*local_path;

	local_path = ft_strjoin("./", cmds->args[0]);
	if (!local_path)
		return (NULL);
	if (access(local_path, X_OK) == 0)
		return (local_path);
	free(local_path);
	return (NULL);
}

char	*handle_path(t_cmd *cmds, t_shell *shell)
{
	char	*path_value;
	char	*res;

	if (!cmds || !cmds->args || !cmds->args[0])
		return (NULL);
	if (ft_strchr(cmds->args[0], '/'))
		return (access_command(cmds));
	path_value = get_env_value(shell, "PATH");
	if (path_lookup_allowed(path_value))
	{
		res = find_cmd_path(cmds, path_value);
		if (res)
			return (res);
	}
	if (!path_lookup_allowed(path_value)
		|| ft_strcmp(cmds->args[0], "minishell") == 0)
		return (resolve_local_path(cmds));
	return (NULL);
}
