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

void	forward_signal(pid_t child_pid, int signun)
{

}

// this mimics the behaviour of ctrl-c
// ctrl-c aborts current input line and gives a fresh prompt (\n)
static void	sigint_handler(int signum)
{
	(void)signum;
	//write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//this mimics the desired behaviour of the ctrl-\ which is do nothing
//set the handler to the sig ignore
//and call sigcation based on that

static void	sigquit_handler(int signum)
{
	struct sigaction	sig_a;

	ft_memset(&sig_a, 0, sizeof(sig_a);
	sig_a.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_a, NULL);
}

//here init an empty set of signals, handler calls the respective functions
void setup_signals(void)
{
    struct sigaction	sa_int;

    sa_int.sa_handler = sigint_handler();
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);

    struct sigaction sa_quit;
    sa_quit.sa_handler = sigquit_handler();
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

