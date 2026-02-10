/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:48:51 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/10 14:49:17 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	command_count(t_cmd *cmd)
{
	size_t	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

t_cmd	*get_last_command(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

bool	safe_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (false);
	}
	return (true);
}

void	reading_end(int pipefd[2])
{
	if (!safe_dup2(pipefd[0], STDIN_FILENO))
		return ;
	close(pipefd[0]);
	close(pipefd[1]);
}

void	writing_end(int pipefd[2])
{
	if (!safe_dup2(pipefd[1], STDOUT_FILENO))
		return ;
	close(pipefd[1]);
	close(pipefd[2]);
}
