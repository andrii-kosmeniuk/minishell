/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:59:22 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/05 14:59:23 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	restore_interactive_signals(void)
{
	setup_interactive_signals();
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
}

int	handle_signal_event(void)
{
	if (g_signal == 130)
	{
		rl_done = 1;
	}
	return (0);
}
