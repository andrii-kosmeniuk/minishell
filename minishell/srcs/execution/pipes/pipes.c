/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:21:34 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/09 13:21:46 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	fork_one_child(t_cmd *cmd, t_shell *shell, pid_t *pids,
						  t_pipes *state)
{
	pid_t	pid;

	if (state->has_next && !safe_pipe(state->cur_pipe))
		return (0);
	pid = fork();
	if (pid == -1)
	{
		fork_error();
		if (state->has_next)
			close(state->cur_pipe);
		return (0);
	}
	if (pid == 0)
		handle_pipeline_child(cmd, shell, state); //yet to be coded
	pids[state->i] = pid;
	handle_pipeline_parent(state); // yet to be coded
}

static int	fork_children(t_cmd *cmd, t_shell *shell, pid_t *pids)
{
	t_pipes	state;
	t_cmd	*cur;
	int		exit_status;

	init_pipe_state(&state);
	cur = cmd;
	while (cur)
	{
		state.has_next = (cmd->next != NULL);
		if (!fork_single_child(cmd, shell, pids, &state))
			return (clean_pipeline(pids, state.i));
		cmd = cmd->next;
		state.i++;
	}
	if (state.prev[0] != -1)
		close(state.prev_pipe);
	parent_signal_setup();
	exit_status = wait_for_all(pids, state.i);
	restore_interactive_signals();
	return (exit_status);
}

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	int		cmd_count;
	pidt	*pids;
	int		exit_status;

	cmd_count = command_count(cmd);
	pids = ft_calloc(command_count, sizeof(pid_t));
	if (!pids)
		return (perror("malloc"), 1);
	exit_status = fork_children(cmd, shell, pids, cmd_count);
	free(pids);
	return (exit_status);
}
