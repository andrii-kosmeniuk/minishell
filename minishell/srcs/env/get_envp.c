/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:20:22 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/26 22:50:00 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	build_minimum_env(t_shell *shell, t_data *data)
{
	t_env	*node;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	node = create_node("PWD", pwd);
	if (!node)
		return (free(pwd), free_env_list(&shell->environment_p));
	node->exported = true;
	free(pwd);
	add_to_list(&shell->environment_p, node);
	node = create_node("SHLVL", "1");
	if (!node)
		return (free_env_list(&shell->environment_p));
	node->exported = true;
	data->shlvl = 1;
	add_to_list(&shell->environment_p, node);
	node = create_node("_", "/usr/bin/env");
	if (!node)
		return (free_env_list(&shell->environment_p));
	node->exported = true;
	add_to_list(&shell->environment_p, node);
}

static t_env	*empty_env(char **envp, t_shell *shell, t_data *data)
{
	if (!envp || !envp[0])
	{
		build_minimum_env(shell, data);
		return (shell->environment_p);
	}
	return (NULL);
}

t_env	*list_key_value(t_shell *shell, char **envp, t_data *data)
{
	shell->environment_p = NULL;
	if (empty_env(envp, shell, data) == NULL)
		return (build_from_envp(shell, envp));
	return (shell->environment_p);
}
