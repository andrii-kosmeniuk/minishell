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
static void	clean_child(t_cmd *cmd, t_shell *shell, pid_t *pids, int code)
{
	command_not_found_error(cmd->args[0]);
	free_command(cmd);
	cleanup_shell(shell);
	free(pids);
	exit(code);
}

static void	clean_execve_failure(t_cmd *cmd, t_shell *shell, char **array,
									pid_t *pids)
{
	free_command(cmd);
	cleanup_shell(shell);
	free_array(array);
	free(pids);
	exit (126);
}

void	execute_in_child(t_cmd *cmd, t_shell *shell, pid_t *pids)
{
	char	**env;

	if (builtin_check(cmd))
	{
		handle_builtin(cmd, shell, shell->environment_p);
		free_command(cmd);
		cleanup_shell(shell);
		free(pids);
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
