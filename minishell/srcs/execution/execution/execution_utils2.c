/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:34:42 by akosmeni          #+#    #+#             */
/*   Updated: 2026/02/26 22:25:30 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*access_command(t_cmd *cmd)
{
	char	*command;

	if (!cmd->args || !cmd->args[0])
		return (NULL);
	command = cmd->args[0];
	if (!ft_strchr(command, '/'))
		return (NULL);
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}

int	check_file_access(char *path, int mode)
{
	return (access(path, mode) == 0);
}

char	*get_env_value(t_shell *shell, char *key)
{
	t_env	*current;

	current = shell->environment_p;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
