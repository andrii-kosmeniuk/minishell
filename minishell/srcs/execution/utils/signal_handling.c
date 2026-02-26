/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:07:31 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/26 18:20:31 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	child_signals_setup(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	parent_signal_setup(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	close_pipes(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	init_pipe_state(t_pipes *state)
{
	state->prev_pipe[0] = -1;
	state->prev_pipe[1] = -1;
	state->curr_pipe[0] = -1;
	state->curr_pipe[1] = -1;
	state->i = 0;
	state->has_next = 0;
}

void	close_std_fds(void)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		close(i);
		i++;
	}
}
