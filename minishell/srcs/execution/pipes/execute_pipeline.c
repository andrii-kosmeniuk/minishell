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

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	size_t	cmd_count;
	pid_t	*pids;
	int		exit_status;

	cmd_count = command_count(cmd);
	pids = ft_calloc(cmd_count, sizeof(pid_t));
	if (!pids)
		return (perror("malloc"), 1);
	exit_status = fork_children(cmd, shell, pids);
	free(pids);
	return (exit_status);
}
