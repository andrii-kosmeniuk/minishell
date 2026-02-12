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
	if (!cmd->path)
	{
		cmd->path = handle_path(cmd, shell);
		if (!cmd->path)
			exit (1);
	}
	env = list_to_envp(shell);
	if (!env)
		return ;
	execve(cmd->path, cmd->args, env);
	execve_error(cmd->path);
}
