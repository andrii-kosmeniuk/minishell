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

//improve exit codes
void	execute_in_child(t_cmd *cmd, t_shell *shell)
{
	char	**env;

	child_signals_setup();
	if (!apply_redirections(cmd))
		exit(1);
	close_fds();
	env = list_to_envp(shell);
	if (!env)
	{
		perror("env error");
		exit(1);
	}
	if (!cmd->path)
	{
		cmd->path = handle_path(cmd, env);
		if (!cmd->path)
			exit (1);
	}
	execve(cmd->path, cmd->args, env);
	execve_error(cmd->path);
}
