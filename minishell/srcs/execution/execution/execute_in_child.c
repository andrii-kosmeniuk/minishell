/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:27:14 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/26 18:09:24 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	clean_child(t_cmd *cmd, t_shell *shell, pid_t *pids, int code)
{
	command_not_found_error(cmd->args[0]);
	cleanup_shell(shell);
	free(pids);
	close_std_fds();
	exit(code);
}

static void	clean_execve_failure(t_cmd *cmd, t_shell *shell, char **array,
									pid_t *pids)
{
	permission_denied_error(cmd->args[0]);
	cleanup_shell(shell);
	free_array(array);
	close_std_fds();
	free(pids);
	exit (126);
}

void	execute_in_child(t_cmd *cmd, t_shell *shell,
						pid_t *pids)
{
	char	**env;

	if (builtin_check(cmd))
	{
		handle_builtin(cmd, shell, shell->environment_p, pids);
		cleanup_shell(shell);
		close_std_fds();
		exit(shell->exit_status);
	}
	if (!cmd->path)
	{
		cmd->path = handle_path(cmd, shell);
		if (!cmd->path)
			clean_child(cmd, shell, pids, 127);
	}
	env = list_to_envp(shell);
	if (!env)
	{
		cleanup_shell(shell);
		free(pids);
		exit(1);
	}
	execve(cmd->path, cmd->args, env);
	clean_execve_failure(cmd, shell, env, pids);
}
