/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:07:46 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/09 16:09:14 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	output_redirections(t_shell *shell, t_redir *redir)
{
	int	fd;
	int	result;

	if (redir->type == R_OUTPUT)
	{
		fd = open_output_file(shell, redir->target, false);
		if (fd < 0)
			return (-1);
		result = safe_dup2(fd, STDOUT_FILENO);
		close(fd);
		return (result);
	}
	else if (redir->type == R_APPEND)
	{
		fd = open_output_file(shell, redir->target, true);
		if (fd < 0)
			return (-1);
		result = safe_dup2(fd, STDOUT_FILENO);
		close(fd);
		return (result);
	}
	return (0);
}

static int	input_redirections(t_shell *shell, t_redir *redir)
{
	int	fd;
	int	result;

	if (redir->type == R_INPUT)
	{
		fd = open_input_file(shell, redir->target);
		if (fd == -1)
			return (-1);
		result = safe_dup2(fd, STDIN_FILENO);
		close(fd);
		return (result);
	}
	return (0);
}

static int	apply_single_redirection(t_shell *shell, t_redir *redir)
{
	int	result;

	if (redir->type == HERE_DOC)
	{
		result = safe_dup2(redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
		return (result);
	}
	if (redir->type == R_OUTPUT || redir->type == R_APPEND)
		return (output_redirections(shell, redir));
	if (redir->type == R_INPUT)
		return (input_redirections(shell, redir));
	return (0);
}

bool	apply_redirections(t_shell *shell, t_cmd *cmd)
{
	t_redir	*cur;
	int		count;

	count = 0;
	cur = cmd->redirections;
	while (cur)
	{
		count++;
		if (apply_single_redirection(shell, cur) == -1)
			return (false);
		cur = cur->next;
	}
	return (true);
}
