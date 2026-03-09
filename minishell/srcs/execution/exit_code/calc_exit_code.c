/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_exit_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:22:57 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/09 13:23:09 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	wait_for_child(pid_t pids)
{
	int	status;
	int	exit_status;
	int	sig;

	exit_status = 0;
	waitpid(pids, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			exit_status = 130;
		else if (sig == SIGQUIT)
		{
			exit_status = 131;
			printf("Quit (core dumped)\n");
		}
		else
			exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}

int	wait_for_all(pid_t *pids, int count)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < count)
	{
		status = wait_for_child(pids[i]);
		i++;
	}
	return (status);
}
