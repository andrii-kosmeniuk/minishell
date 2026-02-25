/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 19:53:23 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/10 19:53:38 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	execute_redirections_only(t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (!apply_redirections(cmd))
	{
		safe_dup2(saved_stdin, STDIN_FILENO);
		safe_dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	safe_dup2(saved_stdin, STDIN_FILENO);
	safe_dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (0);
}

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	size_t	cmd_count;
	pid_t	*pids;
	int		exit_status;

	if (!cmd->args)
	{
		if (cmd->redirections)
		{
			execute_redirections_only(cmd);
		}
		return (0);
	}
	cmd_count = command_count(cmd);
	pids = ft_calloc(cmd_count, sizeof(pid_t));
	if (!pids)
		return (perror("malloc"), 1);
	exit_status = execute_children_parent(cmd, shell, pids);
	free(pids);
	pids = NULL;
	return (exit_status);
}
