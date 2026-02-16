/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:27:14 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/09 13:27:25 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//still go over the free inside children
void	execute_in_child(t_cmd *cmd, t_shell *shell, pid_t *pids)
{
	char	**env;

	if (builtin_check(cmd))
	{
		handle_builtin(cmd, shell);
		free_command(cmd);
		cleanup_shell(shell);
		free(pids);
		exit(shell->exit_status);
	}
	if (!cmd->path)
	{
		cmd->path = handle_path(cmd, shell);
		if (!cmd->path)
		{
			command_not_found_error(cmd->args[0]);
			free_command(cmd);
			cleanup_shell(shell);
			free(pids);
			exit(127);
		}
	}
	env = list_to_envp(shell);
	if (!env)
	{
		cleanup_shell(shell);
		free(pids);
		exit(1);
	}
	execve(cmd->path, cmd->args, env);
	free_command(cmd);
	cleanup_shell(shell);
	free_array(env);
	free(pids);
	exit(126);
}
