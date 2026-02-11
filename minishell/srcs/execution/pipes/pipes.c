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

static int	cleanup_pipe(pid_t *pids, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pids[i] > 0)
			kill(pids[i], SIGKILL);
		i++;
	}
	return (1);
}

static void	handle_pipeline_parent(t_pipes *state)
{
	if (state->prev_pipe[0] != -1)
		close_pipe(state->prev_pipe);
	if (state->has_next)
	{
		state->prev_pipe[0] = state->curr_pipe[0];
		state->prev_pipe[1] = state->curr_pipe[1];
	}
	else
	{
		state->prev_pipe[0] = -1;
		state->prev_pipe[1] = -1;
	}
}

static void	handle_pipeline_child(t_cmd *cmd, t_shell *shell,
									t_pipes *state)
{
	child_signals_setup();
	if (state->i > 0)
		reading_end(state->prev_pipe);
	if (state->has_next)
		writing_end(state->curr_pipe);
	if (!apply_redirections(cmd))
		exit (1);
	close_fds();
	execute_in_child(cmd, shell);
}

static int	fork_one_child(t_cmd *cmd, t_shell *shell, pid_t *pids,
							t_pipes *state)
{
	pid_t	pid;

	if (state->has_next && !safe_pipe(state->curr_pipe))
		return (0);
	pid = fork();
	if (pid == -1)
	{
		fork_error();
		if (state->has_next)
			close_pipe(state->curr_pipe);
		return (0);
	}
	if (pid == 0)
		handle_pipeline_child(cmd, shell, state);
	pids[state->i] = pid;
	handle_pipeline_parent(state);
	return (1);
}

int	fork_children(t_cmd *cmd, t_shell *shell, pid_t *pids)
{
	t_pipes	state;
	t_cmd	*cur;
	int		exit_status;

	init_pipe_state(&state);
	cur = cmd;
	while (cur)
	{
		state.has_next = (cur->next != NULL);
		if (!fork_one_child(cmd, shell, pids, &state))
			return (cleanup_pipe(pids, state.i));
		cur = cur->next;
		state.i++;
	}
	if (state.prev_pipe[0] != -1)
		close_pipe(state.prev_pipe);
	parent_signal_setup();
	exit_status = wait_for_all(pids, state.i);
	restore_interactive_signals();
	return (exit_status);
}
