/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:2e:44 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/09 13:20:57 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	execute_simple_command(t_cmd *cmd, t_shell *shell, pid_t *pids)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid == -1)
		return (fork_error(), 1);
	if (pid == 0)
		execute_in_child(cmd, shell, pids);
	close_heredoc_fds(cmd);
	parent_signal_setup();
	exit_status = wait_for_child(pid);
	restore_interactive_signals();
	unlink_files(cmd);
	return (exit_status);
}
