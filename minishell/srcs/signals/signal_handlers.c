/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:23:07 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/24 22:23:08 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_signal = 2;
	write(STDOUT_FILENO, "\n", 1);
	rl_done = 1;
}

int	handle_heredoc_signal_event(void)
{
	if (g_signal == 2)
	{
		rl_done = 1;
	}
	return (0);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = heredoc_sigint_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	rl_event_hook = handle_heredoc_signal_event;
}

void	setup_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	rl_event_hook = handle_signal_event;
}
